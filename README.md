Trabalho 2 de SOB

Manipular o módulo de kernel que implemente o sistema de arquivos minix em sistemas operacionais Linux, de forma que os arquivos dos usuários sejam armazenados de maneira cifrada.
1- Inserir o parâmetro key a chave simétrica que será usada para cifrar e decifrar o conteúdo dos arquivos
2- Formatar para usar o sistema de arquivos minix modificado
3-  Ao receber dados deve criptografar pelo módulo minix no momento de sua criação ou atualização utilizando o algoritmo AES com a chave fornecida durante a carga do módulo.
4-  Enquanto recebe os dados, o conteúdo do arquivo deve ser descriptografado pelo módulo minix utilizando o algoritmo AES com a chave fornecida durante a carga do módulo.
5-  Para testar que  a criptografia foi de fato realizada, o módulo minix modificado deve ser descarregado e o módulo minix inalterado deve ser carregado. Neste caso, o conteúdo dos arquivos ainda estará acessível aos programas de usuário, mas será apresentado o conteúdo original armazenado de forma criptografada. 

