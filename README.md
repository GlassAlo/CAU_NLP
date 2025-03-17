# NLP Project - Game Data Fetcher

## GitHub Repository
https://github.com/GlassAlo/CAU_NLP#

## Description

The `fetcher.py` script retrieves video game data from [IGDB](https://www.igdb.com/) and creates files for each retrieved game. These files can then be used to perform information retrieval on this data corpus.

## Features

- Retrieves an OAuth access token from the Twitch API.
- Uses the IGDB wrapper to make requests to the IGDB API.
- Retrieves video game data, including alternative names, involved companies, release dates, language supports, external games, age ratings, and more.
- Replaces IDs with readable names for genres, platforms, game modes, themes, player perspectives, franchises, game engines, keywords, and similar games.
- Converts Unix timestamps to readable dates.
- Saves game data in JSON files in a specified directory.

## Dependencies

- `requests`
- `python-dotenv`
- `igdb-api-v4`

You can install the dependencies using pip:
```sh
pip install requests python-dotenv igdb-api-v4
```
## Usage

1. Make sure you have a `.env` file with your Twitch client ID and client secret (https://dev.twitch.tv/console/apps):
    ```
    CLIENT_ID = 'your_client_id'
    CLIENT_SECRET = 'your_client_secret'
    ```

2. Run the `fetcher.py` script:
To get information about the arguments, run:

    ```sh
    python fetcher.py --help
    ```

- To fetch data for a specific number of games, use the `--limit` argument.
- To save the data in a specific directory, use the `--directory` argument.
- To fetch data for random games, use the `--random` argument.:

```sh
python fetcher.py --limit <> --directory <> --random <>
```

3. JSON files containing game data will be created in the `games_data` directory.

## Source

[IGDB](https://www.igdb.com/)