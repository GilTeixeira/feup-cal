# Concepção e Análise de algoritmos
MIEIC 2016/2017

### Tema: Agência de Viagens
#### (Parte 1)

Uma agência de viagens auxilia os seus clientes na pesquisa das melhores soluções para a marcação de viagens e respetivo alojamento. 
Neste trabalho, pretende-se implementar um sistema que permita à agência de viagens conseguir uma seleção mais criteriosa de uma solução de acordo com as necessidades do seu cliente, procurando sempre minimizar o seu custo. 
Considere que o custo das viagens (bilhetes de avião, por ex.) é fixo para o período a considerar. Mas o preço do alojamento varia de acordo com o dia da semana ou período específico (festividade local, por ex.).
O cliente especifica: 
- origem e destino para a sua viagem, ou
- conjunto de locais que pretende visitar na viagem
O cliente pode ainda especificar um tempo limite para realizar a viagem.
Avalie a conectividade do grafo, a fim de evitar que locais a visitar se encontrem em zonas inacessíveis.

#### (Parte2)

Para a segunda parte deste trabalho, considere que o cliente oferece uma lista de nomes de lugares e pontos de interesse a serem incluídos no seu itinerário. Os pontos de interesses podem ser monumentos, ou lugares numa cidade. A agência de viagem deverá pesquisar, na lista dos seus destinos, aqueles que estão incluídos na lista do cliente, e/ou possuem os pontos de interesses que o cliente deseja visitar durante a sua viagem. Por exemplo, o cliente pode desejar visitar a “Torre dos Clérigos” e a agência deve ser capaz de lhe incluir a cidade do Porto, como destino no seu itinerário. Implemente esta funcionalidade, considerando tanto pesquisa exata, assim como pesquisa aproximada, das strings identificativas dos nomes de cidades e pontos de interesse. O resultado da pesquisa exata deverá indicar se existe ou não o lugar desejado. Para a pesquisa aproximada, deverá retornar uma lista com os resultados mais próximos daquilo que se procura.

Estas novas funcionalidades deverão ser integradas no trabalho já realizado para a primeira parte. Avalie a complexidade (teórica e empiricamente) dos algoritmos implementados em função dos dados de input usados.
