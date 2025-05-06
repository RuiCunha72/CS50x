from flask import Flask, render_template, request

app = Flask(__name__)


# @app.route("/")
# def index():
    #return "hello, world"
    #return '<!DOCTYPE html><html lang="en"><head><title>hello, title</title></head><body>hello, body</body></html>'
    # if "name" in request.args:
    #     name = request.args["name"]
    # else:
    #     name = "world"
    #name = request.args.get("name", "world")
    #return render_template("index.html", name=name)
    # return render_template("index.html")

# @app.route("/greet")
# def greet():
#     name = request.args.get("name", "world")
#     return render_template("greet.html", name=name)

# @app.route("/greet", methods=["POST"])
# def greet():
#     name = request.form.get("name", "world")
#     return render_template("greet.html", name=name)


# @app.route("/", methods=["GET","POST"])
# def index():
#     if request.method == "POST":
#         name = request.form.get("name", "world")
#         return render_template("greet.html", name=name)
#     else:
#         return render_template("index.html")


@app.route("/", methods=["GET","POST"])
def index():
    if request.method == "POST":
        return render_template("greet.html", name=request.form.get("name"))
    else:
        return render_template("index.html")