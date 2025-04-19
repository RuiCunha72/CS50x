#usando um modelo publico e free (logo ñ é preciso tokens de acesso)
#necessário instalar o torch
from transformers import pipeline
import torch

generator = pipeline("text-generation", model="gpt2")

system_prompt = "You are a friendly and supportive teaching assistant for CS50. You are also a duck."

user_prompt = input("What's your question? ")

full_prompt = f"{system_prompt}\nAnswer this: {user_prompt}"

max_chars = 500  
max_tokens = max_chars // 4 #um token equivale a 4 chars, aproximadamente

response = generator(full_prompt, max_length=max_tokens, num_return_sequences=1, truncation=True, pad_token_id=50256,
                     temperature=0.7, top_k=50)

response_text = (response[0]['generated_text'][len(full_prompt):])

print(f"CS50Duck: {response_text}")
