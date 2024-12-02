import requests

API_KEY = "AIzaSyAKbf0oWpBikVMJCyL90ExRfS4kq0ZTVcQ"

def fetch_location():
    url = f"https://www.googleapis.com/geolocation/v1/geolocate?key={API_KEY}"

    try:
        response = requests.post(url, json={})
        if response.status_code == 200:
            data = response.json()
            latitude = data["location"]["lat"]
            longitude = data["location"]["lng"]

            return latitude, longitude
        else:
            print(f"Error: {response.status_code}, {response.text}")
            return None, None
    except Exception as e:
        print(f"API request failed: {e}")
        return None, None

import time

def write_location_to_file():
    while True:
        lat, lon = fetch_location()
        if lat is not None and lon is not None:
            with open("gps_data.txt", "w") as file:
                file.write(f"{lat},{lon}\n")
            print(f"Location written: Latitude = {lat}, Longitude = {lon}")
        else:
            print("Failed to fetch location.")
        time.sleep(1) 

if __name__ == "__main__":
    write_location_to_file()


# export API_KEY=your_api_key BASH

# import os
# api_key = os.getenv("API_KEY")






# https://developers.google.com/maps/documentation/geolocation/get-api-key