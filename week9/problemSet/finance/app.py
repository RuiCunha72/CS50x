import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime
from collections import defaultdict

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # Creates dictionary for erevy purchase the user logged has made
    user_id = session.get("user_id")
    portfolio_data = db.execute("""
        SELECT symbol, SUM(CASE WHEN transaction_type = 'BUY' THEN shares
                                 WHEN transaction_type = 'SELL' THEN -shares
                                 ELSE 0 END) AS total_shares
        FROM transactions
        WHERE user_id = ?
        GROUP BY symbol
        """, user_id)
    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]


    # Creates a new portfolio
    portfolio = []

    for item in portfolio_data:
        quote = lookup(item["symbol"])
        if quote: 
            portfolio.append({
                # Adds to the portfolio the name of the quote
                "name": quote["name"],
                # Adds to the portfolio the symbol
                "symbol": item["symbol"],
                # Add to the portfolio the shares of the purchase
                "shares": item["total_shares"],
                # Add to the portfolio the current price of the quote
                "price": quote["price"],
                # Add to the portfolio the current balance for that share
                "total": item["total_shares"] * quote["price"]
            })

    # Calculte the total of holdings for the user
    total_sum = sum(item["total"] for item in portfolio)
    return render_template("index.html", portfolio=portfolio, cash=cash, total_sum=total_sum)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure stock symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide stock symbol", 400)
        
        # Ensure a share exists
        if not request.form.get("shares"):
            return apology("must provide a share amount", 400)
        
        # Stores the result of the lookup
        symbol = request.form.get("symbol")
        stock = lookup(symbol)

        # Ensure stock symbol is valid
        if not stock or "error" in stock:
            return apology("invalid stock symbol", 400)

        # Stores the amount of shares
        try:
            shares = int(request.form.get("shares"))
        except ValueError:
            return apology("invalid number of shares", 400)

        # Ensure the share amount is valid
        if not shares > 0:
            return apology("must provide a valid share amount (>0)", 400)

        # Stores the quote regardind the stock searched
        price = stock["price"]

        # Stores the cash the user has
        user_id = session.get("user_id")
        cash_result = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        cash = cash_result[0]["cash"]

        # Ensure the user has the cash to buy the shares he wants
        if shares*price > cash:
            return apology("u r poor :(", 400)

        # When the purchase is valid
        timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", shares*price, user_id)
        db.execute("INSERT INTO transactions (user_id, symbol, price, shares, date, transaction_type) VALUES (?, ?, ?, ?, ?, ?)", user_id, symbol, price, 
                   shares, timestamp, "BUY")
        return redirect("/")
    
    # User reached route via POST (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Creates dictionary for erevy purchase the user logged has made
    transactions = db.execute("SELECT id, symbol, price, shares, date, transaction_type FROM transactions WHERE user_id = ?", session.get("user_id"))

    # Creates a new portfolio
    portfolio = []

    # For every purchase in the aggregated dictionary
    for transaction in transactions:
        portfolio.append({
            "id": transaction["id"],
            "symbol": transaction["symbol"],
            "shares": transaction["shares"],
            "price": transaction["price"],
            "date": transaction["date"],
            "transaction_type": transaction["transaction_type"]
        })

    return render_template("history.html", portfolio=portfolio)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure stock symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide stock symbol", 400)
        
        # Stores the result of the lookup
        stock = lookup(request.form.get("symbol"))

        # Ensure stock symbol is valid
        if not stock or "error" in stock:
            return apology("invalid stock symbol", 400)

        # Tries to get the quote regarind the stock searched
        try:
            return render_template("quoted.html", name=stock["name"], price=usd(stock["price"]), symbol=stock["symbol"])
        except Exception as e:
            return apology(f"Error: {e}", 500)
    
    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")

    


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)
        
        # Ensure password confirmation was submitted
        elif not request.form.get("confirmation"):
            return apology("must provide password confirmation", 400)
        
        # Ensure password and password confirmation are the same
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords do not match", 400)

        # Registring
        username = request.form.get("username")
        password = generate_password_hash(request.form.get("password"))
        # If there is no error insert the values to the database
        try:
            rows = db.execute(
                "INSERT INTO users (username, hash) VALUES (?, ?)", username, password
            )
        # Otherwise the exception will be thrown and the user is informed that the username already exists
        # except Exception as e:
        #     return apology(f"Error: {e}", 403)
        except:
            return apology("the username selected already exists")
        
        return redirect("/")
        
    else:
        
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():

    """Show portfolio of stocks"""
    # Creates dictionary for erevy purchase the user logged has made
    user_id = session.get("user_id")
    portfolio_data = db.execute("""
        SELECT symbol, SUM(CASE WHEN transaction_type = 'BUY' THEN shares
                                 WHEN transaction_type = 'SELL' THEN -shares
                                 ELSE 0 END) AS total_shares
        FROM transactions
        WHERE user_id = ?
        GROUP BY symbol
        """, user_id)

    # Creates a new portfolio
    portfolio = []

    for item in portfolio_data:
        quote = lookup(item["symbol"])
        if quote: 
            portfolio.append({
                # Adds to the portfolio the name of the quote
                "name": quote["name"],
                # Adds to the portfolio the symbol
                "symbol": item["symbol"],
                # Add to the portfolio the shares of the purchase
                "shares": item["total_shares"],
                # Add to the portfolio the current price of the quote
                "price": quote["price"],
                # Add to the portfolio the current balance for that share
                "total": item["total_shares"] * quote["price"]
            })


    """Sell shares of stock"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure stock symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide stock symbol", 400)
        
        # Ensure a share exists
        if not request.form.get("shares"):
            return apology("must provide a share amount", 400)
        
        # Stores the result of the lookup
        symbol = request.form.get("symbol")
        stock = lookup(symbol)

        for stock in portfolio:
            if symbol == stock["symbol"]:
                shares = int(request.form.get("shares"))
                price = stock["price"]
                if shares > stock["shares"]: # When the selling is not valid
                    return apology("u don't have that amount of shares for the requested quote", 400)
                else: # When the selling is valid
                    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
                    db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", shares*price, user_id)
                    db.execute("INSERT INTO transactions (user_id, symbol, price, shares, date, transaction_type) VALUES (?, ?, ?, ?, ?, ?)", user_id, symbol, price, 
                               shares, timestamp, "SELL")
                    return redirect("/")
    
    # User reached route via POST (as by clicking a link or via redirect)
    else:
        symbols = [item["symbol"] for item in portfolio]
        return render_template("sell.html", portfolio=portfolio, symbols=symbols)