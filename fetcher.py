import os
import re
import json
import requests
import time
import argparse
import random
from datetime import datetime
from dotenv import load_dotenv
from igdb.wrapper import IGDBWrapper

# Load environment variables
load_dotenv()
CLIENT_ID = os.getenv('CLIENT_ID')
CLIENT_SECRET = os.getenv('CLIENT_SECRET')

# Function to get OAuth token from Twitch API


def get_access_token():
    url = "https://id.twitch.tv/oauth2/token"
    params = {
        "client_id": CLIENT_ID,
        "client_secret": CLIENT_SECRET,
        "grant_type": "client_credentials"
    }
    response = requests.post(url, params=params)
    response.raise_for_status()
    return response.json()["access_token"]


# Retrieve and set access token
ACCESS_TOKEN = get_access_token()
wrapper = IGDBWrapper(CLIENT_ID, ACCESS_TOKEN)

def get_game_data(limit=10, randomBool=False):
    id = random.randint(1, 10000)

    response = wrapper.api_request(
        'games', f'fields *; exclude screenshots, tags, websites, cover, artworks, bundles, videos; limit 1; where id = {id};')
    return response

def get_games_data(limit=10, random=False):
    if random:
        games_data = []
        for _ in range(limit):
            game_data = json.loads(get_game_data())
            games_data.append(game_data[0])
            time.sleep(0.25)
        return games_data
    response = wrapper.api_request(
        'games', f'fields *; exclude screenshots, tags, websites, cover, artworks, bundles, videos; limit {limit};')
    return json.loads(response)


def get_names(endpoint, ids):
    if not ids:
        return []
    response = wrapper.api_request(
        endpoint, f'fields name; where id = ({", ".join(map(str, ids))});')
    return [item['name'] for item in json.loads(response)]


def get_parent_game(parent_id):
    if not parent_id:
        return None
    response = wrapper.api_request(
        'games', f'fields name; where id = {parent_id};')
    data = json.loads(response)
    return data[0]['name'] if data else None


def get_external_games(external_ids):
    if not external_ids:
        return []
    response = wrapper.api_request(
        'external_games', f'fields game; where id = ({", ".join(map(str, external_ids))});')
    data = json.loads(response)
    return get_names('games', [item['game'] for item in data])


def get_age_ratings(rating_ids):
    if not rating_ids:
        return []
    response = wrapper.api_request(
        'age_ratings', f'fields category, rating; where id = ({", ".join(map(str, rating_ids))});')
    ratings_map = {
        1: "Three",
        2: "Seven",
        3: "Twelve",
        4: "Sixteen",
        5: "Eighteen",
        6: "RP",
        7: "EC",
        8: "E",
        9: "E10",
        10: "T",
        11: "M",
        12: "AO"
    }
    return [ratings_map.get(item['rating'], "Unknown") for item in json.loads(response) if 'rating' in item]


def get_alternative_names(name_ids):
    if not name_ids:
        return []
    response = wrapper.api_request(
        'alternative_names', f'fields name; where id = ({", ".join(map(str, name_ids))});')
    return [item['name'] for item in json.loads(response)]


def get_involved_companies(company_ids):
    if not company_ids:
        return {"developers": [], "publishers": []}
    response = wrapper.api_request(
        'involved_companies', f'fields company, developer, publisher; where id = ({", ".join(map(str, company_ids))});')
    companies = json.loads(response)
    developers = [c['company'] for c in companies if c.get('developer')]
    publishers = [c['company'] for c in companies if c.get('publisher')]
    return {"developers": get_names('companies', developers), "publishers": get_names('companies', publishers)}


def get_release_dates(release_ids):
    if not release_ids:
        return []
    response = wrapper.api_request(
        'release_dates', f'fields human; where id = ({", ".join(map(str, release_ids))});')
    return [item['human'] for item in json.loads(response)]


def get_language_supports(language_ids):
    if not language_ids:
        return []
    response = wrapper.api_request(
        'language_supports', f'fields language.name; where id = ({", ".join(map(str, language_ids))});')
    return [item['language']['name'] for item in json.loads(response) if 'language' in item]


def get_category_name(category_id):
    categories = {
        0: "Main Game",
        1: "DLC",
        2: "Expansion",
        3: "Bundle",
        4: "Standalone Expansion",
        5: "Mod",
        6: "Episode",
        7: "Season",
        8: "Remake",
        9: "Remaster",
        10: "Expanded Game",
        11: "Port",
        12: "Fork",
        13: "Pack",
        14: "Update"
    }
    return categories.get(category_id, "Unknown")


def get_game_type_name(game_type_id):
    game_types = {
        0: "Unknown",
        1: "Main Game",
        2: "DLC",
        3: "Expansion",
        4: "Bundle",
        5: "Standalone Expansion",
        6: "Mod",
        7: "Episode",
        8: "Season",
        9: "Remake",
        10: "Remaster",
        11: "Expanded Game",
        12: "Port",
        13: "Fork",
        14: "Pack",
        15: "Update"
    }
    return game_types.get(game_type_id, "Unknown")


def convert_unix_timestamp(timestamp):
    if not timestamp:
        return None
    return datetime.utcfromtimestamp(timestamp).strftime('%Y-%m-%d %H:%M:%S')


def get_version_parent(version_parent_id):
    if not version_parent_id:
        return None
    response = wrapper.api_request(
        'games', f'fields name; where id = {version_parent_id};')
    data = json.loads(response)
    return data[0]['name'] if data else None


def replace_ids_with_names(game):
    for field, endpoint in {
        'genres': 'genres',
        'platforms': 'platforms',
        'game_modes': 'game_modes',
        'themes': 'themes',
        'player_perspectives': 'player_perspectives',
        'franchises': 'franchises',
        'game_engines': 'game_engines',
        'keywords': 'keywords',
        'similar_games': 'games',
    }.items():
        game[field] = get_names(endpoint, game.get(field, []))

    company_data = get_involved_companies(game.get('involved_companies', []))
    game['developers'] = company_data['developers']
    game['publishers'] = company_data['publishers']

    game['release_dates'] = get_release_dates(game.get('release_dates', []))
    game['language_supports'] = get_language_supports(
        game.get('language_supports', []))
    game['external_games'] = get_external_games(game.get('external_games', []))
    game['age_ratings'] = get_age_ratings(game.get('age_ratings', []))
    game['alternative_names'] = get_alternative_names(
        game.get('alternative_names', []))

    if 'parent_game' in game and game['parent_game']:
        game['parent_game'] = get_parent_game(game['parent_game'])

    if 'version_parent' in game and game['version_parent']:
        game['version_parent'] = get_version_parent(game['version_parent'])

    game['created_at'] = convert_unix_timestamp(game.get('created_at'))
    game['updated_at'] = convert_unix_timestamp(game.get('updated_at'))
    game['first_release_date'] = convert_unix_timestamp(
        game.get('first_release_date'))

    game['category'] = get_category_name(game.get('category'))
    game['game_type'] = get_game_type_name(game.get('game_type'))

    # Remove involved_companies after extracting developers and publishers
    if 'involved_companies' in game:
        del game['involved_companies']

    return game


def sanitize_filename(name):
    return re.sub(r'[^a-zA-Z0-9-_ ]', '', name).strip()


def save_games_to_files(games, directory='games_data'):
    if not os.path.exists(directory):
        os.makedirs(directory)
    for game in games:
        game = replace_ids_with_names(game)
        game_name = sanitize_filename(game.get('name', 'Unknown_Game'))
        filename = os.path.join(directory, f'{game_name}.json')
        with open(filename, 'w', encoding='utf-8') as file:
            json.dump(game, file, indent=4, ensure_ascii=False)
            print(f"Game data saved to {filename}")


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Fetch and save game data from IGDB.')
    parser.add_argument('--limit', type=int, default=100, help='Number of games to fetch')
    parser.add_argument('--directory', type=str, default='games_data', help='Directory to save game data files')
    parser.add_argument('--random', type=bool, default=False, help='Fetch random games')
    args = parser.parse_args()

    games_data = get_games_data(limit=args.limit, random=args.random)
    save_games_to_files(games_data)
    print("Games data saved successfully!")
