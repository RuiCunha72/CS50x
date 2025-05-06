# Implements a registration form using a select menu without validating sport server-side
from cs50 import SQL
from flask import Flask, render_template, request

app = Flask(__name__)

db = SQL("sqlite:///froshims.db")

SPORTS = [
    "Baskteball",
    "Soccer",
    "Ultimate Frisbee",
]

# REGISTRANTS = {

# }

@app.route("/")
def index():
    return render_template("index.html", sports=SPORTS)


# @app.route("/register", methods=["POST"])
# def register():

#     # Validate submission
#     if not request.form.get("name") or request.form.get("sport") not in SPORTS:
#         return render_template("failure.html")

#     # Confirm registration
#     return render_template("success.html")


@app.route("/register", methods=["POST"])
def register():

    name = request.form.get("name")
    if not name:
        return render_template("error.html", message="Missing name")

    sport = request.form.get("sport")
    if not sport:
        return render_template("error.html", message="Missing sport")
    if sport not in SPORTS:
        return render_template("error.html", message="Invalid Sport")
    
    # REGISTRANTS[name] = sport
    db.execute("INSERT INTO registrants (name, sport) VALUES(?, ?)", name, sport)

    return render_template(("success.html"))

@app.route("/registrants")
def registrants():
    #return render_template("registrants.html", registrants=REGISTRANTS)
    registrants = db.execute("SELECT name, sport FROM registrants")
    return render_template("registrants.html", registrants=registrants)