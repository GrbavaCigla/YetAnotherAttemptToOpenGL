import requests
from os import path, remove
import zipfile

GLAD_WEB_HOST = "https://glad.dav1d.de/generate"
GLAD_WEB_FORM_DATA = {
    "language": "c",
    "specification": "gl",
    "api": "gl=3.3",
    "profile": "core",
    "loader": "on"
}

project_root = path.dirname(path.dirname(__file__))

resp = requests.post(GLAD_WEB_HOST, data=GLAD_WEB_FORM_DATA)
zip_url = resp.url + "glad.zip"

filepath = path.join(project_root, "glad.zip")

with open(filepath, "wb+") as file:
    file.write(requests.get(zip_url).content)

with zipfile.ZipFile(filepath, "r") as zip_ref:
    zip_ref.extractall(project_root)

remove(filepath)