📦 API de Gerenciamento de Estoque com Spring Boot
https://img.shields.io/badge/Spring_Boot-2.7.5-green
https://img.shields.io/badge/License-MIT-blue

Uma API RESTful completa para controle de estoque, desenvolvida em Spring Boot, com operações CRUD e arquitetura em camadas.

🚀 Funcionalidades
✔ Cadastro de produtos (nome, quantidade, preço)
✔ Consulta por ID ou listagem completa
✔ Atualização e remoção de itens
✔ Validações básicas e respostas HTTP semânticas

🛠 Tecnologias
Java 11

Spring Boot (Web, DevTools)

JSON para troca de dados

Maven para gerenciamento de dependências

🔌 Endpoints
Método	Endpoint	Descrição
POST	/produtos	Adiciona novo produto
GET	/produtos	Lista todos os produtos
GET	/produtos/{id}	Busca produto por ID
PUT	/produtos/{id}	Atualiza produto existente
DELETE	/produtos/{id}	Remove produto do estoque
Exemplo de requisição (POST):

json
{
    "id": 1,
    "nome": "Teclado",
    "quantidade": 50,
    "preco": 199.90
}
⚙️ Como Executar
Pré-requisitos:

JDK 11+

Maven 3.6+

Clone o repositório:

bash
git clone https://github.com/DAVIMEDX/API-REST.git
Execute a aplicação:

bash
cd API-REST
mvn spring-boot:run
A API estará disponível em: http://localhost:8080

🧪 Testando a API
Use Postman ou cURL:

bash
# Listar produtos
curl http://localhost:8080/produtos

# Adicionar produto
curl -X POST -H "Content-Type: application/json" \
-d '{"id":1,"nome":"Mouse","quantidade":30,"preco":89.90}' \
http://localhost:8080/produtos
📂 Estrutura do Projeto
text
src/
├── main/
│   ├── java/
│   │   └── com/exemplo/estoqueapi/
│   │       ├── controller/  # Endpoints REST
│   │       ├── model/       # Entidade Produto
│   │       ├── service/     # Lógica de negócio
│   │       └── EstoqueApiApplication.java
│   └── resources/
│       └── application.properties
📌 Melhorias Futuras
Integrar banco de dados (H2/MySQL)

Adicionar autenticação JWT

Implementar Swagger para documentação

Criar testes automatizados

📜 Licença
Este projeto está sob a licença MIT. Veja o arquivo LICENSE para detalhes.

Desenvolvido por [DAVIMEDX] 👨‍💻
