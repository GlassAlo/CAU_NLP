import os
import re
import json
import requests
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

def get_games_data(limit=10):
    response = wrapper.api_request('games', f'fields *; exclude screenshots, tags, websites; limit {limit};')
    return json.loads(response)

def get_names(endpoint, ids):
    if not ids:
        return []
    response = wrapper.api_request(endpoint, f'fields name; where id = ({", ".join(map(str, ids))});')
    return [item['name'] for item in json.loads(response)]

def get_parent_game(parent_id):
    if not parent_id:
        return None
    response = wrapper.api_request('games', f'fields name; where id = {parent_id};')
    data = json.loads(response)
    return data[0]['name'] if data else None

def get_involved_companies(company_ids):
    if not company_ids:
        return {"developers": [], "publishers": []}
    response = wrapper.api_request('involved_companies', f'fields company, developer, publisher; where id = ({", ".join(map(str, company_ids))});')
    companies = json.loads(response)
    developers = [c['company'] for c in companies if c.get('developer')]
    publishers = [c['company'] for c in companies if c.get('publisher')]
    return {"developers": get_names('companies', developers), "publishers": get_names('companies', publishers)}

def get_release_dates(release_ids):
    if not release_ids:
        return []
    response = wrapper.api_request('release_dates', f'fields human; where id = ({", ".join(map(str, release_ids))});')
    return [item['human'] for item in json.loads(response)]

def get_language_supports(language_ids):
    if not language_ids:
        return []
    response = wrapper.api_request('language_supports', f'fields language.name; where id = ({", ".join(map(str, language_ids))});')
    return [item['language']['name'] for item in json.loads(response) if 'language' in item]

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
    game['language_supports'] = get_language_supports(game.get('language_supports', []))
    
    if 'parent_game' in game and game['parent_game']:
        game['parent_game'] = get_parent_game(game['parent_game'])
    
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

if __name__ == '__main__':
    games_data = get_games_data(limit=10)
    save_games_to_files(games_data)
