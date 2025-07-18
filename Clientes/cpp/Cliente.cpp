#include <iostream>
#include <string>
#include <curl/curl.h>

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void http_request(const std::string& url, const std::string& method, const std::string& data = "") {
    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Erro ao iniciar curl\n";
        return;
    }

    std::string readBuffer;
    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, method.c_str());
    if (method == "POST" || method == "PUT") {
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
    }
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    CURLcode res = curl_easy_perform(curl);
    long http_code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

    if (res != CURLE_OK) {
        std::cerr << "curl_easy_perform() falhou: " << curl_easy_strerror(res) << std::endl;
    } else {
        std::cout << method << " " << url << " resposta (HTTP " << http_code << "):\n" << readBuffer << "\n";

        // Mensagens customizadas de erro
        if (http_code == 404) {
            std::cout << "❌ Erro: Recurso não encontrado.\n";
        } else if (http_code == 400) {
            std::cout << "❌ Erro: Requisição inválida.\n";
        } else if (http_code == 500) {
            std::cout << "❌ Erro: Problema no servidor.\n";
        }
    }

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
}

void listarProdutos(const std::string& base_url) {
    http_request(base_url, "GET");
}

void buscarProduto(const std::string& base_url) {
    std::cout << "Digite o ID do produto para buscar: ";
    int id;
    std::cin >> id;
    if (id < 1) {
        std::cout << "❌ ID inválido.\n";
        return;
    }
    http_request(base_url + "/" + std::to_string(id), "GET");
}

void adicionarProduto(const std::string& base_url) {
    int id, quantidade;
    double preco;
    std::string nome;

    std::cout << "ID: ";
    std::cin >> id;
    std::cin.ignore();
    std::cout << "Nome: ";
    std::getline(std::cin, nome);
    std::cout << "Quantidade: ";
    std::cin >> quantidade;
    std::cout << "Preço: ";
    std::cin >> preco;

    std::string json = "{\"id\":" + std::to_string(id) +
                       ",\"nome\":\"" + nome +
                       "\",\"quantidade\":" + std::to_string(quantidade) +
                       ",\"preco\":" + std::to_string(preco) + "}";

    http_request(base_url, "POST", json);
}

void atualizarProduto(const std::string& base_url) {
    int id, quantidade;
    double preco;
    std::string nome;

    std::cout << "ID do produto a atualizar: ";
    std::cin >> id;
    if (id < 1) {
        std::cout << "❌ ID inválido.\n";
        return;
    }
    std::cin.ignore();
    std::cout << "Novo nome: ";
    std::getline(std::cin, nome);
    std::cout << "Nova quantidade: ";
    std::cin >> quantidade;
    std::cout << "Novo preço: ";
    std::cin >> preco;

    std::string json = "{\"id\":" + std::to_string(id) +
                       ",\"nome\":\"" + nome +
                       "\",\"quantidade\":" + std::to_string(quantidade) +
                       ",\"preco\":" + std::to_string(preco) + "}";

    http_request(base_url + "/" + std::to_string(id), "PUT", json);
}

void removerProduto(const std::string& base_url) {
    std::cout << "Digite o ID do produto para remover: ";
    int id;
    std::cin >> id;
    if (id < 1) {
        std::cout << "❌ ID inválido.\n";
        return;
    }
    http_request(base_url + "/" + std::to_string(id), "DELETE");
}

int main() {
    std::string base_url = "http://localhost:8080/produtos";
    int opcao = -1;

    while (opcao != 0) {
        std::cout << "\nMenu:\n"
                  << "1 - Listar produtos\n"
                  << "2 - Buscar produto por ID\n"
                  << "3 - Adicionar produto\n"
                  << "4 - Atualizar produto\n"
                  << "5 - Remover produto\n"
                  << "0 - Sair\n"
                  << "Escolha uma opção: ";
        std::cin >> opcao;
        std::cin.ignore();

        switch (opcao) {
            case 1:
                listarProdutos(base_url);
                break;
            case 2:
                buscarProduto(base_url);
                break;
            case 3:
                adicionarProduto(base_url);
                break;
            case 4:
                atualizarProduto(base_url);
                break;
            case 5:
                removerProduto(base_url);
                break;
            case 0:
                std::cout << "Saindo...\n";
                break;
            default:
                std::cout << "❌ Opção inválida, tente novamente.\n";
        }
    }

    return 0;
}
