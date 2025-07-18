package com.exemplo.estoqueapi.service;

import com.exemplo.estoqueapi.model.Produto;

import java.util.List;


public interface EstoqueService {
    void adicionarProduto(Produto produto);
    Produto buscarProdutoPorId(int id);
    List<Produto> listarProdutos();
    boolean atualizarProduto(int id, Produto novoProduto);
    boolean removerProduto(int id);
}
