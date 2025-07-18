package com.exemplo.estoqueapi.service;

import com.exemplo.estoqueapi.model.Produto;
import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.List;

@Service
public class EstoqueServiceImpl implements EstoqueService {
    private final List<Produto> produtos = new ArrayList<>();

    @Override
    public void adicionarProduto(Produto produto) {
        produtos.add(produto);
    }

    @Override
    public Produto buscarProdutoPorId(int id) {
        return produtos.stream()
                .filter(p -> p.getId() == id)
                .findFirst()
                .orElse(null);
    }

    @Override
    public List<Produto> listarProdutos() {
        return new ArrayList<>(produtos);
    }

    @Override
    public boolean atualizarProduto(int id, Produto novoProduto) {
    Produto p = buscarProdutoPorId(id);
    if (p == null) {
        return false;
        }
        p.setNome(novoProduto.getNome());
        p.setQuantidade(novoProduto.getQuantidade());
        p.setPreco(novoProduto.getPreco());
        return true;
    }

    @Override
    public boolean removerProduto(int id) {
        Produto p = buscarProdutoPorId(id);
        if (p != null) {
        produtos.remove(p);
        return true;
        }
        return false;
    }
}
