from transformers import pipeline

# Usar o modelo Flan-T5 para geração de texto
pipe = pipeline("text2text-generation", model="google/flan-t5-large")

def processar_sintomas(sintomas):
    # Formatar o prompt para obter conselhos médicos
    prompt = f"Baseado nos sintomas: {sintomas}, forneça um diagnóstico e conselhos médicos."
    resposta = pipe(prompt, max_length=100, num_return_sequences=1, truncation=True)
    return resposta[0]["generated_text"]

if __name__ == "__main__":
    import sys
    sintomas = " ".join(sys.argv[1:])  # Capturar os sintomas passados como argumentos
    print(processar_sintomas(sintomas))