package com.exemplo.estoqueapi.controller;

import com.exemplo.estoqueapi.model.Produto;
import com.exemplo.estoqueapi.service.EstoqueService;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/produtos")
public class ProdutoController {

    @Autowired
    private EstoqueService estoqueService;

    @PostMapping
    public ResponseEntity<Void> adicionarProduto(@RequestBody Produto produto) {
        estoqueService.adicionarProduto(produto);
        return ResponseEntity.ok().build();
    }

    @GetMapping
    public ResponseEntity<List<Produto>> listarProdutos() {
        return ResponseEntity.ok(estoqueService.listarProdutos());
    }

    @GetMapping("/{id}")
    public ResponseEntity<Produto> buscarProdutoPorId(@PathVariable int id) {
        Produto produto = estoqueService.buscarProdutoPorId(id);
        if (produto == null) {
            return ResponseEntity.notFound().build();
        }
        return ResponseEntity.ok(produto);
    }

    @PutMapping("/{id}")
    public ResponseEntity<Void> atualizarProduto(@PathVariable int id, @RequestBody Produto produtoAtualizado) {
        Produto existente = estoqueService.buscarProdutoPorId(id);
            if (existente == null) {
                return ResponseEntity.notFound().build();
            }

        existente.setNome(produtoAtualizado.getNome());
        existente.setQuantidade(produtoAtualizado.getQuantidade());
        existente.setPreco(produtoAtualizado.getPreco());
        return ResponseEntity.noContent().build();
    }


    @DeleteMapping("/{id}")
    public ResponseEntity<String> removerProduto(@PathVariable int id) {
        boolean removido = estoqueService.removerProduto(id);
        if (removido) {
            return ResponseEntity.ok("Produto removido com sucesso.");
        } else {
            return ResponseEntity.notFound().build();
        }
    }
}
