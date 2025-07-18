import requests

BASE_URL = "http://localhost:8080/produtos"

def listar_produtos():
    r = requests.get(BASE_URL)
    print("\n📦 Lista de produtos:")
    print(r.json())

def buscar_produto():
    id = input("Digite o ID do produto para buscar: ")
    r = requests.get(f"{BASE_URL}/{id}")
    if r.status_code == 200:
        print(f"\n🔍 Produto {id}: {r.json()}")
    else:
        print(f"\n❌ Produto {id} não encontrado.")

def adicionar_produto():
    try:
        id = int(input("ID: "))
        nome = input("Nome: ")
        quantidade = int(input("Quantidade: "))
        preco = float(input("Preço: "))
        produto = {"id": id, "nome": nome, "quantidade": quantidade, "preco": preco}
        r = requests.post(BASE_URL, json=produto)
        print(f"\n✅ Adicionar produto: {nome} -> {r.text}")
    except ValueError:
        print("Erro: Insira valores numéricos válidos para ID, quantidade e preço.")

def atualizar_produto():
    try:
        id = int(input("ID do produto a atualizar: "))
        nome = input("Novo nome: ")
        quantidade = int(input("Nova quantidade: "))
        preco = float(input("Novo preço: "))
        produto = {"id": id, "nome": nome, "quantidade": quantidade, "preco": preco}
        r = requests.put(f"{BASE_URL}/{id}", json=produto)
        if r.status_code == 200:
            print(f"\n♻️ Produto {id} atualizado: {r.text}")
        else:
            print(f"\n❌ Erro ao atualizar produto {id}")
    except ValueError:
        print("Erro: Insira valores numéricos válidos para ID, quantidade e preço.")

def remover_produto():
    id = input("Digite o ID do produto para remover: ")
    r = requests.delete(f"{BASE_URL}/{id}")
    if r.status_code == 200:
        print(f"\n🗑️ Produto {id} removido: {r.text}")
    else:
        print(f"\n❌ Erro ao remover produto {id}")

def menu():
    while True:
        print("""
Escolha uma opção:
1 - Listar produtos
2 - Buscar produto por ID
3 - Adicionar produto
4 - Atualizar produto
5 - Remover produto
0 - Sair
""")
        escolha = input("Opção: ")

        if escolha == "1":
            listar_produtos()
        elif escolha == "2":
            buscar_produto()
        elif escolha == "3":
            adicionar_produto()
        elif escolha == "4":
            atualizar_produto()
        elif escolha == "5":
            remover_produto()
        elif escolha == "0":
            print("Saindo...")
            break
        else:
            print("Opção inválida, tente novamente.")

if __name__ == "__main__":
    menu()
