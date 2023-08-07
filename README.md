# 2022-AVL-Tree-Implementation
The proposed problem was to implement a simulator of an email server, using hash table concepts and binary trees.

# Trabalho Prático 3

```
DCC214 - Estrutura de Dados
Igor Joaquim da Silva Costa
```
## 1. Introdução

Oproblemapropostofoiimplementarumsimuladordeumservidordeemails,usando
conceitos de tabela hash e árvores binárias.
Pararesolveroproblemacitado,foiimplementadoumatabelahashsimples,ondeoid
dousuárioseriaachaveparaarmazenarumemailnatabela.Alémdisso,afimdemelhoraro
tempode execução,todoemailna mesmaposiçãodatabelaéarmazenadodentrodeuma
árvore binária AVL, onde o id da mensagem é a chave.
Diantedoexposto,adocumentaçãopresentepossuicomoobjetivodetalharcomoo
sistemafoiimplementado(Seção2),oquãoeficienteelepodeseremtermosteóricos(Seção
3) e aplicados (Seção 5), além de explicar como o programa lida com possíveis
inconsistênciasdurantesuaexecução(Seção4).Porfim,oprojetoésumarizadojuntocomos
aprendizados gerados durante a produção do trabalho(Seção 6).

## 2. Método

Estaseçãotemcomoobjetivodiscutirasdecisõesquelevaramàatualimplementação
do programa.

# 2.1 Fluxo principal

Antesdedetalharcomooprogramaoperasobreumtexto,valediscorrerdemaneira
textualeintuitivaoqueoprogramafazacadapassodeexecução.Primeiramente,osistemaé
capaz deefetuar 3 operações,inserção,buscaeremoção.Diantedisso,paracadalinhado
arquivodeentrada,éavaliadoqualoperaçãodeveserexecutada.Apósisso,éfeitaaoperação
corresponde e o resultado é armazenado no arquivo de saida.


# 2.2 Classes

Afimdesuportarasoperaçõesdescritasacima,sãonecessáriasestruturasrobustaso
suficiente para guardar emails, ids, árvores binárias e tabelas hash. Nesse sentido, foi
implementadoumaclasseparacadaelementodomini-mundodeinteresse.Aseguir,seguea
definição das mesmas:

## 2.2.1 Email

Um email é composto por seusids de usuário e de mensagem, e da mensagem
propriamente dita. Cada email possui uma lista de N palavras chamada mensagem,
representando o texto lido.

## 2.2.2 AVL

Como sãonecessáriasdiversasconsultaseremoçõesduranteoprograma,tornou-se
válidaaimplementaçãodeumaárvoreAVL.Nessesentido,umaAVLéumconjuntodenós
(node_t), onde cada nó possui uma referência aos seus filhos, seu pai e ao conteúdo
armazenado,quenessecasoéoemail.Aindaassim,umnóéresponsávelporcalcularasua
própria altura e a altura dos seus antepassados, além de conhecer o seu fator de
balanceamento.
Dito isso,umaAVL éumaárvorebináriabalanceada,onde,acadaoperação,uma
operaçãoextradebalanceamentoéexecutada,afimdemanterapropriedadedescrita.Sendo
assim, aAVL possui 4 métodosprincipais:Inserção,remoção, pesquisa ebalanceamento.
Após cada inserção e remoção, a função balanceamento é chamada. Para executar o
balanceamento,sãousadas 2 funçõesauxiliaresderotação,quesãoperformadassegundoo
caso que o balanceamento da AVL se encontra.
Noque tangeainserção eremoção, ospossíveiscasosdedesbalanceamentoestão
descritos no código fonte da árvore.

## 2.2.3 Tabela Hash

Para representara tabelaHash,foiimplementadaumalistadinâmicadeAVLS,de
tamanhoN.Sendoassim,cadaiddeusuáriopossuiumaposiçãonatabela,dadapelafunção
de hash id%N.


## 3. Análise de complexidade

# 3.1 Espaço

Cadaemailpossui 3 inteirosdecontroleeumalistadepalavrasdetamanhomáximo
200.Cadanópossuiumareferênciaao seuconteudoeàseusvizinhos,umaárvoreéum
conjuntodeMnós,umatabelapossuiBárvores.Considerandoquetodaposiçãodatabela
hashtenhaomesmonúmeroMdenós,oespaçogastoé𝑂(𝑀*𝐵).AindaassimseNforo
tamanho daentrada ecada árvoretiver Mnós,M=𝑁/𝐵,ou seja,𝑂(𝑁)notamanhoda
entrada.

## 3.1.2 Chamadas recursivas

Comosãofeitasalgumaschamadasrecursivasduranteaexecuçãodoprograma,suas
execuçõespodemocupargrandeespaçonamemória,seoNforsuficientementegrande.Para
o balanceamento e a operação de atualizar altura de um nó, o nó atual segue fazendo
chamadas recursivas até alcançar a raiz, sabe-se que a distância entre um nó folha de uma
árvorebalanceadaatéaraizéde𝑂(𝑙𝑜𝑔(𝑁)).Nessecaso,cadainserção/remoçãopreenche
cerca de𝑂(𝑙𝑜𝑔(𝑁))de espaço, durante a execuçãodo progrma.

# 3.2 Tempo

```
Para análise de tempo, considere N como o número de elementos na árvore.
```
## 3.2.1 Inserção

Paraserealizarainserção,éfeitaumabuscabináriapelaposiçãoqueonovoelemento
deveserinserido.Considerandoacomparaçãocomooperaçãomaissignificativa,éconhecido
quetalbuscaefetua𝑂(𝑙𝑜𝑔(𝑁))comparações.Entretanto,apósinserirumnónaárvoreAVL,
deve-se recalcular as alturas do novo nó até a raiz, além de rebalancear a árvore.Para
atualizaraalturadeumúniconó,ouexecutarseubalanceamento,gasta-se 𝑂( 1 ),jáqueessas
operações só acessam elementosque jáestão armazenados dentroda estrutura nó. Para
executaressasoperações donóatéaraiz,sãogastosmais𝑂(𝑙𝑜𝑔(𝑁))passos.Aindaassim,a
complexidade geral da inserção se mantém𝑂(𝑙𝑜𝑔(𝑁)).


## 3.2.2 Busca

Considerandoacomparaçãocomoaoperaçãomaissignificativa,quetodabuscarum
elemento performa o mesmo passo a passo da inserção. Dessa forma, a busca é𝑂(𝑙𝑜𝑔(𝑁)).

## 3.2.3 Remoção

Paraserealizararemoção,primeiroénecessáriobuscaroelementoaserremovido.
Considerandoa comparaçãocomooperaçãomaissignificativa, éconhecido quetalbusca
efetua𝑂(𝑙𝑜𝑔(𝑁))comparações,dadootópicoanterior.Nessesentido,seoelementonãofoi
encontrado,aremoçãoterminaaqui.Casooelementosejaencontrado,existem 2 casosase
considerar.Seoelementofornófolha,outiversóumfilho,aremoçãoexecutamaisO(1)
operações, já que só são executadas operações que acessam elementos que já estão
armazenados dentroda estrutura nó. Nocasodonó com 2 filhos,a estratégiausada foi
substituí-lopeloseuantecessor,ouseja,omaiorelementodasubárvoreàesquerdadonó.
Encontrar esse elemento também ocorre 𝑂(𝑙𝑜𝑔(𝑁)), já que estamos buscando o maior
elementodeumaárvorebináriabalanceada.Aindaassim,acomplexidadedopiorcaso,caso
médio e melhor caso da remoção se mantém𝑂(𝑙𝑜𝑔(𝑁)).

## 3.2.4 Complexidade Geral.

Ditoisso,acomplexidadegeraldaordenaçãocorrespondeaquantidadedeoperações
executadas,vezesumfatorde log(N),que correspondeaocustodeexecutartaloperação.
Sendo B o tamanho de operações presentes no arquivo de entrada, o programa executa em
𝑂(𝐵*𝑙𝑜𝑔(𝑁))
Onde N é a média dos tamanhos das árvores.
Por fim, as operações de inserção, remoção e consulta na tabela hash ocorrem na
mesma complexidade que as mesmas operações na árvore AVL.

## 4. Estratégias de Robustez

Umproblemaencontradoduranteaimplementaçãodosistemafoilidarcomarquivos
deentradagrandes.Dessaforma,arquivoscommaisde 50000 linhaspodemapresentarerros
de leitura durante a execução do programa.


## 5. Análise Experimental

Aanáliseexperimentalaseguirtemcomoobjetivomediroquãoeficienteéosistema
implementadousandoduasmétricas,odesempenhocomputacional-quãorápidooprograma
é executado com entradas grandes - e análises de acesso em memória.

# 5.1 Desempenho computacional

## 5.1.1 Perfil de execução

Para testarodesempenhocomputacional,primeiramente,oprogramafoicompilado
em estadode "profiling",a fimde analisarquais funções consomemrelativamentemais
tempoduranteaexecuçãodoprograma.Diantedisso,foramfeitasbateriasdetestesapartir
de entradasgeradasaleatoriamenteporumprograma pythonimplementadopeloaluno.O
testeaseguirfoifeitoporumaentradacompostapor 1000 inserções, 100 remoçõese 1500
buscas. Com o profile das execuçõespronto, cadaexecuçãoéprocessadapeloprograma
“gprof”,umaferramentaque auxilianaanálise dodesempenhocomputacional.Dito isso,
segue a análise das chamadas de funções.

```
Tempo de
execução
(%)
```
```
Calls
```
```
45. 51 15051 arvore::pesquisa(int, int)
18. 20 172965 int std::max<int>(int const&, int const&)
18.20 10001 arvore::insere(email*)
9.10 10001 tabelaH::insere(email*)
9.10 1 main
0.00 235449 node_t::fator_balanceamento()
0.00 19301 node_t::atualiza_altura()
0.00 10101 arvore::balanceia(node_t*)
```
Para evitar redundância, os outros perfis de execução apresentam o mesmo
comportamento dotesteapresentadoacima.Noquetangeaanálisedosexperimentos,fica
evidentequeafunçãoquemaisdemandatempo,emporcentagem,éafunçãoparapesquisaro
elementonaárvore,vistoqueelafoiaoperaçãomaisabundantenoarquivodeentrada,além


desernecessáriaparaexecutararemoção.Paraalémdisso,afunçãoapresentacomplexidade
logarítmicanotamanhomédiodaárvore,gastandocercade 1500 * 𝑙𝑜𝑔(𝑁)emtempode
execuçãoduranteoprograma,usandoafórmuladesenvolvidanaseção3.2.2.Dessaforma,a
funçãodepesquisaestaremprimeirolugarnãoédegrandesurpresa,emboraexistamformas
de diminuir esse tempo de execução usando de técnicas como hashing.
Afunçãoqueocupaasegundaposiçãoéafunçãoqueselecionaomáximoentredois
valoresinteiros,usadoduranteaatualizaçãodaalturadaárvore.Talfunçãogastarmaistempo
deexecuçãoqueaprópriafunçãodeatualizaralturarevelaquetalvezexistamformasmais
eficientes de recuperar o máximo entre dois valores, melhorando a performance do programa.
O terceiro e quarto lugar se tratam da inserção de elementos na tabela. Como
esperado,elasacontecemtodasasvezesqueexisteainserção,sendojustoelasficaremabaixo
daoperaçãodebuscanoperfildeexecução,vistoqueacontecem50%maisbuscasdoque
inserções no teste.
Emboraasfunçõesdeatualizaralturaebalanceamentosejamchamadasváriasvezes
duranteoprograma,elasrepresentamumtempodeexecuçãoquaseinsignificante.Talevento
podeserexplicadopelofatodeserraroacontecerumainserçãoouremoçãoquedesbalanceie
aárvoredeformaasercustosoocorrerobalanceamento.Aindaassim,afunçãodecalcularo
fatorde desbalanceamentofoiexecutada omaiornúmerodevezes,o quetambémnão é
estranho.
Nessesentido,conclui-sequeaindaexistemmargensparaamelhoranodesempenho
doprograma,aníveldechamadasdefunções,vistoquemuitasdelaspoderiamserfeitasde
outras formas, a fim de melhor utilizar tempo de execução do programa.

## 5.1.2 Desempenho em termos da entrada

Alémdotempogasto pelaschamadasde funções, deve-semedirarelaçãoentreo
aumentodovolumedaentradadoprogramacomoseutempodeexecução.Pararealizartal
objetivo,foiutilizadaaferramentaMemlogdoprofessorWagnerMeiraeferramentasparaa
geração de gráficos. A seguir, o gráfico com os resultados.


Como visto acima,o tempo de execuçãocrescemuitopróximoa N,ondeNé a
quantidade de operações feitas assim como foi discutido na seção de análise de complexidade.

# 5.2 Análise de localidade de referência e acesso de memória

Comoexplicadoemaula,programaseficientesemusodememóriasãoaquelesque
tendemaacessarregiõesdememóriacontíguas,jáqueessapráticaéotimizadapelossistemas
operacionais onde o programa é executado. Tal propriedade échamadade localidadede
referência e é uma ótima métrica de como o programa acessa a memória por ele utilizada.
Nessesentido,munidodasferramentasAnalisamemeMemlog,disponibilizadaspelo
professorWagnerMeira,épossívelgerargráficosquedemonstramoacessodememóriado
programaemsuasdiversasfases,e,assim,analisarseoacessodememóriadoprograma
segue as boas práticas desejadas. Dito isso, segue a análise de acesso de memória e
localidadedereferência,ondeoid 0 representaainserçãodoselementosnaárvore,oid 1 os
acessosduranteo balanceamento,oid 2 comoosacessosdurantepesquisaseoid 3 os
acessos feitos durante a remoção.




Comovistoacima,oprogramaacessadiversasvezesposiçõesdememóriadistantes,
issoaconteceporque oselementossãoarmazenadosdeformadinâmica,desfavorecendoa
localidade de referência. Nos ids 0 e 1, podemosenxergarumaformade triângulo,que
corresponde a busca binária durante as primeiras inserções feitas, visto que, durante a
primeira população dos dados, existe muita memória livre, podendo-se armazenardados
próximos emposiçõescontíguasnamemória.Nocasodosids2, 4 e 1 duranteasegunda
metadedaexecução,ográficomostraoefeitodabuscabinárianamemória.Comomuitos
dadosjáforamrotacionadoseremovidos,elementosfilhosdeumnódaárvoretendemaficar
distantesnamemória,desfavorecendoalocalidadedereferênciaquandoseprecisarealizar
umabusca. Dessaforma,éesperadoqueadistânciadepilhasejaalta,vistoqueelementos
distantes na memória são acessados e trocadosde posiçãodurante toda a execução do
programa.
A seguir, estão os histogramas de distância de pilha do programa:



Dessa forma,conclui-se que o sistema não mantémumabaixa distânciadepilha
durantea execução,configurandoum pontonegativo noque tangeaométodousadopara
armazenar os dados do trabalho.


## 6. Conclusões

Com o intuito de simular um sistema de troca de emails entre usuários, foi
implementadoum programa que utilizaestruturasdedados quemantéma ordenaçãode
forma não trivial para resolver o problema.
Duranteoprojetodosistemaforamlevadasemconsideraçãonãosóaspectospráticos
doprocessamentodetexto,mastambémcomoalinguagemdeprogramaçãoescolhidapoderia
serumaferramentaútil parachegarnoobjetivo esperado.Todaaquestãode mapearum
mini-mundo de interesse em um modelo computacional robusto se mostrou bastante
produtiva, levando o aluno a pensar em formas criativas de se resolver e entender o
problema, tendo como resultado uma extensa prática técnica, principalmente ao se
implementarumaárvoreAVLcompletaerobusta.Porfim,otempoextrausadoparaprojetar
osistematrouxeváriasrecompensasnosentidodaimplementação,sendoumaspectoaser
levado para trabalhos futuros.
Além disso,os testese aanálise decomplexidade semostraram muitoúteispara
entendercomoasentradasinfluenciamaexecuçãodoprogramaecomoalgunsdetalhesde
implementação podem ser significativos em termos de desempenho computacional e
localidade de referência.
Nessesentido,todoofluxodetrabalhofoiessencialparaaconsolidaçãodeconteúdos
aprendidos emsala, além de apresentar,de formaprática,comosoftwaresmaiores, mais
consistentes e robustos são projetados e implementados.

## 7. Bibliografia:

Ziviani,N.(2006).ProjetosdeAlgoritmoscomImplementaçõesemJavaeC++:Capítulo3:
Estruturas de Dados Básicas. Editora Cengage.

Paulo Feofiloff, Notas de Aula da disciplina Projeto de Algoritmos (2018). DCC-IME-USP.
disponível em:https://www.ime.usp.br/~pf/algoritmos/aulas/


## 8. Instruções para compilação e execução:

## 8.1 Compilação

Existempartesdoprogramaquesãocompatíveisapenasàsversõesmaisrecentesda
linguagem c++, dito isso, deve-se seguir as seguintes configurações para a compilação:

```
Linguagem: C++
Compilador: Gnu g++
Flags de compilação:-std=c++11 -g
Versão da linguagem: standard C++1 1
Sistema operacional (preferência): distribuições baseadas no kernel Linux 5.15.
```
Ocomandoparacompilaroprogramaautomaticamenteestápresentenoarquivo **“Makefile”**
esuaexecuçãoéchamadapelocomando **“makeall”** .Aindaassim,seguemasinstruçõespara
compilar manualmente:

Parageraroexecutáveldoprograma,énecessário,primeiro,geraroobjetoparacadaarquivo
presentenapasta“/src”.Talobjetivopodeseralcançadoseguindoosseguintescomandosem
ordem:

```
g++ -std=c++11 -Wall -pg -c src/memlog.cpp -o obj/memlog.o -I./include/
g++ -std=c++11 -Wall -pg -c src/arvore.cpp -o obj/arvore.o -I./include/
g++ -std=c++11 -Wall -pg -c src/node.cpp -o obj/node.o -I./include/
g++ -std=c++11 -Wall -pg -c src/main.cpp -o obj/main.o -I./include/
g++ -std=c++11 -Wall -pg -c src/email.cpp -o obj/email.o -I./include/
g++ -std=c++11 -Wall -pg -c src/hash.cpp -o obj/hash.o -I./include/
```
Apósessepasso,deve-sejuntartodososobjetosemumúnicoarquivoexecutável,seguindoo
comando:
g++ -std=c++11 -Wall -pg -o ./bin/tp3.out ./obj/memlog.o ./obj/arvore.o ./obj/node.o
./obj/main.o ./obj/email.o ./obj/hash.o

Deste modo, o executável “/bin/tp3.out” estará compilado e pronto para ser utilizado.


### 8.2 Execução

```
Seguem as instruções para a execução manual:
```
1. Certifique-se que o compilável foigeradode maneiracorreta,sealgum problema
    ocorrer, execute o comando “make all” presente no “Makefile”.
2. Dadoqueocompilávelfoigeradodemaneiracorreta,certifique-sequeoarquivode
    entrada existe. Se ele não existir, crie-o.
3. Certifique-sequeoarquivodeentradaestánaformataçãoesperada,ondeexisteum
    inteiro na primeira linha do arquivo, seguido pelas operações especificadas.
4. Uma vez que os passos anteriores foram cumpridos, executeo programa com o
    comando: ./bin/tp3.out -i (entrada) -o (saida)
5. A saída estará guardada no arquivo de saida.


