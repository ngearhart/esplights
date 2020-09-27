from flask import Flask, render_template


app = Flask("ESP Lights",
            static_folder="./frontend/dist/static",
            template_folder="./frontend/dist")


@app.route('/', defaults={'path': ''})
@app.route('/<path:path>')
def catch_all(path):

    return render_template("index.html")