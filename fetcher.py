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

def get_game_data():
    id = random.randint(1, 100000)

    response = wrapper.api_request(
        'games', f'fields name, summary; limit 1; where id = {id};')
    return response

def get_games_data(limit=10, random=False):
    if random:
        games_data = []
        for _ in range(limit):
            game_data = json.loads(get_game_data())
            if len(game_data) > 0:
                games_data.append(game_data[0])
            time.sleep(0.25)
        return games_data
    response = wrapper.api_request(
        'games', f'fields name, summary; limit {limit};')
    return json.loads(response)

def sanitize_filename(name):
    return re.sub(r'[^a-zA-Z0-9-_ ]', '', name).strip()

def save_games_to_files(games, directory='games_data'):
    if not os.path.exists(directory):
        os.makedirs(directory)
    for game in games:
        game_name = sanitize_filename(game.get('name', 'Unknown_Game'))
        filename = os.path.join(directory, f'{game_name}.json')
        with open(filename, 'w', encoding='utf-8') as file:
            summary = game.get('summary', 'No summary available.')
            summary = '\n'.join(summary.split('. '))
            file.write(summary)
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
