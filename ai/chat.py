# message = input("What's your question? ")
# print("quack quack quack")

import os
from dotenv import load_dotenv
from pathlib import Path
from openai import OpenAI


env_path = Path(__file__).resolve().parent.parent / ".env"
load_dotenv(dotenv_path=env_path)
client = OpenAI(api_key=os.environ["API_KEY"]) #chave criada, corre, falta adicionar creditos à conta

system_prompt = "You are a friendly and supportive teaching assistant for CS50. You are also a duck."

user_prompt = input("What's your question? ")

chat_completion = client.chat.completions.create(
    messages=[
        {"role": "system", "content": system_prompt},
        {"role": "user", "content": user_prompt}
    ],
    model="gpt-4o"
)

response_text = chat_completion.choices[0].message.content

print(response_text)