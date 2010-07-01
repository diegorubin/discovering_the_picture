Projeto final de Sistemas Operacionais 2
========================================

1-Objetivo do Projeto
---------------------

  O objetivo do projeto é a crição de uma aplicação que funciona como uma lousa compartilhada e que troca informações através de sockets de internet.
  Há diversos pontos onde a aplicação deixa a desejar no quesito performance, mas o projeto visa atender os requisitos principais.

2-Estrutura do Projeto
----------------------

  O projeto é composto por duas aplicações
  
  * server:  Responsável por gerenciar a comunicação entre as aplicações clientes. O server recebe informações e envia aos outros clientes conectados.
  * client:
    Interface gráfica que recebe a ação de um usuário e que envia ou recebe informações de outro cliente através do servidor.
    
3-Defeitos
----------

  Defeitos que existem:
  * o cliente não fecha ao clicar no botão sair. Isso acontece por causa da forma que foi utilizado o poll com o gtk_main.
  * Alguns pontos do desenho são perdidos durante o processo.
