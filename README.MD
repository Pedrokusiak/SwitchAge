
Aluno: Pedro Henrique Santos Kusiak
# RELATORIO VIDEO 01: Resolução de Colisão 2D - Pixel Perfect

Este documento detalha como funciona a resolução de colisão em jogos 2D, com foco na abordagem de **Colisão Pixel Perfect** e sua implementação em um sistema onde a distância de interseção entre objetos é usada para corrigir a posição de forma precisa.

---

## 📚 Introdução

Colisões são fundamentais para jogos 2D, sendo responsáveis por garantir interações realistas entre os objetos. Neste projeto, optamos pela abordagem **Pixel Perfect** para a detecção de colisões, por ser a mais precisa, especialmente em objetos com formas irregulares. 

O modelo de resolução adotado corrige a posição dos objetos com base na profundidade da colisão, calculando a distância de interseção e ajustando os objetos na direção oposta para evitar sobreposição.

---

## ⚙️ Processo de Resolução

O sistema de colisão foi dividido nas seguintes etapas:

### 1. Detecção de Colisão - Pixel Perfect

Nesta etapa, verificamos se os pixels visíveis de dois objetos colidem. Este método é particularmente útil em sprites irregulares, onde métodos como bounding boxes podem gerar falsos positivos. O processo inclui:
- Comparação de pixels opacos entre os dois sprites.
- Identificação da área de interseção, com base nas coordenadas dos pixels sobrepostos.

Essa abordagem garante maior precisão, mas exige maior processamento, o que é adequado para jogos com número limitado de colisões simultâneas.

---

### 2. Resolução de Colisão

Após a detecção, resolvemos a colisão movendo os objetos de forma a eliminar a sobreposição. O modelo adotado utiliza a **distância de interseção** para corrigir a posição dos objetos. O processo funciona da seguinte maneira:

1. **Calcular a Distância de Penetração:**
   Identificamos a profundidade da interseção em ambos os eixos (X e Y).

2. **Determinar a Direção de Ajuste:**
   Escolhemos a menor distância de interseção (X ou Y) como o eixo de separação principal. 
   - Se a colisão for mais profunda no eixo X, ajustamos as posições horizontalmente.
   - Se for no eixo Y, ajustamos verticalmente.

3. **Empurrar na Direção Contrária:**
   Movemos o objeto em direção oposta à interseção, usando a profundidade da colisão calculada. Isso impede que os objetos se sobreponham.

---

### 3. Verificação Pós-Colisão

Após a separação, verificamos se:
- Os objetos ainda estão em colisão (o que pode ocorrer devido a múltiplas colisões simultâneas).
- As velocidades e direções dos objetos precisam ser ajustadas para simular a física desejada (como ricochete ou atrito).

---

## 📊 Modelo de Resolução

O modelo adotado se encaixa na categoria de **Resolução Vetorial Baseada em Penetração**, pois utiliza a profundidade de interseção para determinar o ajuste necessário. Essa abordagem é ideal para:
- Garantir que os objetos nunca se sobreponham.
- Evitar tremulações ou instabilidades comuns em sistemas de correção imprecisos.

No modelo, a separação acontece de forma proporcional ao grau de interseção, o que garante fluidez e consistência no movimento.

---

## 🛠️ Vantagens da Abordagem

1. **Precisão Máxima:** Evita falsos positivos e simula colisões detalhadas para objetos com bordas complexas.
2. **Controle sobre Resolução:** O ajuste baseado na distância de penetração permite um controle refinado sobre a resposta.
3. **Realismo:** Movimentos corrigidos suavemente criam uma experiência mais imersiva.

---

## ⚠️ Desafios e Considerações

- **Desempenho:** A detecção Pixel Perfect exige maior processamento, o que pode limitar seu uso em jogos com muitos objetos.
- **Gerenciamento de Casos Limite:** Colisões em múltiplos eixos simultâneos requerem lógica adicional para evitar resultados inesperados.

---

## 📌 Conclusão

A abordagem de colisão **Pixel Perfect** combinada com o modelo de ajuste vetorial baseado na profundidade de penetração oferece precisão e robustez. É ideal para jogos 2D que requerem alta fidelidade visual e física, garantindo que os objetos nunca se sobreponham e se comportem de forma realista durante colisões.

Link para o video: https://drive.google.com/file/d/1YFc3anE-F2MHOfi5HEXWrqvOYG-hxCV_/view?usp=sharing


# RELATORIO VIDEO 02: MixerManager - Implementação de Áudio com SDL2_mixer

Este documento detalha a implementação e abordagem da classe `MixerManager`, desenvolvida para gerenciar o áudio de um projeto utilizando a biblioteca **SDL2_mixer**. A classe encapsula funcionalidades de carregamento, reprodução e controle de músicas e efeitos sonoros.

---

## 📚 Introdução

A `MixerManager` foi projetada para facilitar a manipulação de áudio em projetos, oferecendo uma interface amigável para controlar músicas e efeitos sonoros com base na biblioteca **SDL2_mixer**. A implementação adota práticas modernas, como o uso de smart pointers, tratamento robusto de erros e estrutura de dados eficiente.

---

## ⚙️ Funcionalidades Implementadas

### **1. Inicialização e Finalização**

- **Inicialização (`initialize`)**: Configura a biblioteca SDL2_mixer, especificando taxa de amostragem, formato de áudio, número de canais e tamanho do buffer. Qualquer falha durante a inicialização gera um erro descritivo.

- **Finalização**: No destrutor (`~MixerManager`), todos os recursos de áudio são liberados automaticamente.

---

### **2. Carregamento de Áudio**

- **Carregar Músicas (`loadMusic`)**:
  Permite carregar arquivos de música (ex.: MP3, OGG) e associá-los a um identificador único para reprodução posterior.

- **Carregar Efeitos Sonoros (`loadSound`)**:
  Permite carregar arquivos curtos de som (ex.: WAV) e armazená-los para uso em efeitos sonoros.

---

### **3. Reprodução e Controle**

- **Reprodução de Música (`playMusic`)**:
  Reproduz músicas carregadas a partir de seu identificador. Suporta reprodução contínua (loop infinito) ou única.

- **Reprodução de Efeitos Sonoros (`playSound`)**:
  Reproduz sons em canais livres. Caso nenhum canal esteja disponível, reutiliza canais ocupados.

- **Controle de Reprodução**:
  Métodos como `stopMusic`, `pauseMusic` e `resumeMusic` permitem controlar a reprodução atual de músicas.

---

### **4. Ajuste de Volume**

- **Volume de Música (`setMusicVolume`)**:
  Ajusta o volume da música atual, com valores entre `0` (mudo) e `128` (máximo).

- **Volume de Efeitos Sonoros (`setSoundVolume`)**:
  Ajusta o volume global para todos os efeitos sonoros.

---

## 🛠️ Abordagem Técnica

### **1. Uso de Smart Pointers**

Os recursos de áudio carregados são gerenciados por `std::unique_ptr` com functors personalizados (`Mix_FreeMusic` e `Mix_FreeChunk`). Essa abordagem:
- Garante a liberação automática de memória.
- Previne vazamentos de recursos.

### **2. Estrutura de Dados Eficiente**

- Músicas e sons são armazenados em `std::unordered_map`, permitindo buscas rápidas por identificadores.

### **3. Tratamento de Erros**

- Mensagens de erro detalhadas são geradas pelo método `throwSDLMixerError`, centralizando o gerenciamento de falhas e facilitando a depuração.

---

## 📊 Vantagens

- **Modularidade**: A `MixerManager` encapsula toda a lógica de áudio, tornando o código mais organizado.
- **Reutilização de Recursos**: Sons e músicas são carregados uma vez e reutilizados conforme necessário.
- **Facilidade de Controle**: Métodos claros para manipulação de áudio garantem simplicidade no uso.

---

## ⚠️ Limitações e Melhorias Futuras

1. **Gerenciamento Avançado de Canais**:
   - Implementar lógica para priorizar sons críticos ou ajustar dinamicamente o número de canais.

2. **Adição de Filtros**:
   - Suporte a fade-in e fade-out em músicas e sons.

3. **Configurações Globais**:
   - Salvar e restaurar volumes ou configurações de áudio ao reiniciar o jogo.

---

## 📝 Conclusão

A `MixerManager` oferece uma solução robusta e eficiente para integrar áudio em projetos baseados em SDL2. Com um design modular e técnicas modernas, é uma ferramenta poderosa para criar experiências auditivas imersivas em jogos ou outras aplicações multimídia.

Link para o video: https://drive.google.com/file/d/1VM1ZR0peBQSPkaYfEv0y8r3HxdFKqtR7/view?usp=sharing


# RELATORIO 03 :# Physics Class

## 📖 Introdução

- A classe `Physics` é um motor de física 2D projetado para simular comportamentos realistas em jogos e simulações.
- Permite gerenciar forças, gravidade, aceleração e velocidade de forma eficiente.
- Proporciona uma experiência dinâmica e natural para objetos em movimento.

## ⚙️ Importância do Motor de Física

- **Realismo**: Simula interações físicas como gravidade, resistência e aceleração.
- **Simplicidade**: Facilita a implementação de comportamentos físicos complexos.
- **Flexibilidade**: Oferece personalização de propriedades como massa e gravidade para atender diferentes cenários.

## 🛠️ Métodos e Funcionalidades

### 🔧 Construtor
Physics(Vector2D gravity, float mass);

- **Inicialização**:
  - Atributos principais: gravidade, massa, força, aceleração e velocidade.
- **Validação**:
  - Lança uma exceção se a massa for zero, garantindo cálculos consistentes.

### ➡️ applyForce(const Vector2D& force)
- **Descrição**:
  - Aplica uma força ao objeto, acumulando diferentes interações (gravidade, vento, etc.).
- **Exemplo de Uso**:
  - Ideal para simular empurrões ou mudanças repentinas no movimento.

### 🔄 update(float deltaTime)
- **Descrição**:
  - Atualiza o estado físico do objeto com base no tempo decorrido.
- **Funcionamento**:
  - **Cálculo da Aceleração**:
    - Baseada nas forças acumuladas e na gravidade.
  - **Atualização da Velocidade**:
    - Modifica a velocidade do objeto com base na aceleração.
  - **Resistência do Ar**:
    - Reduz gradualmente a velocidade para simular perda de energia.
  - **Limitação de Velocidade**:
    - Garante que o movimento não ultrapasse um limite máximo.
  - **Reset das Forças**:
    - Prepara o objeto para o próximo ciclo de cálculos.

### 🔍 getters e setters
- **getters**:
  - Métodos como `getVelocity` e `getForce` permitem acessar atributos da classe.
- **setters**:
  - Métodos como `setVelocity` e `setGravity` controlam os estados físicos do objeto.
- **Transição Suave de Gravidade**:
  - O método `setGravity` realiza mudanças graduais para simular alterações naturais no ambiente.

## ✅ Conclusão

- **Modularidade**:
  - A classe `Physics` é uma ferramenta eficiente para gerenciar dinâmicas físicas em ambientes 2D.
- **Facilidade de Uso**:
  - Oferece uma base sólida para o desenvolvimento de jogos e simulações interativas.
- **Realismo e Controle**:
  - Proporciona movimentos naturais com alta capacidade de personalização.

LINK para o video:

# RELATORIO 04 :# Classe de testes 

## 📖 Introdução

A classe `TestSuite` foi desenvolvida para testar manualmente os principais métodos e funcionalidades da classe `Physics` e de outras classes associadas, como `Vector2D`. Optamos por testes manuais devido à simplicidade e ao baixo número de casos de teste necessários para validar o comportamento do sistema. Essa abordagem foi mais adequada e eficiente do que a utilização de um framework de testes, considerando o escopo limitado dos testes.

## ⚙️ Benefícios da Abordagem Manual

- **Simplicidade**: A lógica de testes é clara e fácil de implementar diretamente no código.
- **Rápida Implementação**: Não há necessidade de configurar dependências externas, como frameworks de teste.
- **Leveza**: Como os testes necessários eram poucos e bem delimitados, a abordagem manual reduziu a complexidade geral.
- **Foco nos Casos Relevantes**: Permitiu direcionar o esforço apenas para os aspectos essenciais da classe.

## 🛠️ Funcionalidades Testadas

### 📐 Testes para Vector2D
- **Adição de Vetores**:
  - Verifica se a operação de soma retorna os valores esperados.
- **Multiplicação por Escalar**:
  - Testa a multiplicação de um vetor por um número escalar.
- **Divisão por Escalar**:
  - Valida se a divisão de um vetor por um número retorna os valores corretos.
- **Divisão por Zero**:
  - Confirma que a operação gera valores infinitos, conforme esperado.

### 🧪 Testes para Physics
- **Construtor**:
  - Verifica se os atributos iniciais, como gravidade, massa e velocidade, são configurados corretamente.
- **Aplicação de Força**:
  - Testa se a força aplicada modifica a velocidade do objeto de forma adequada.
- **Atualização Baseada no Tempo**:
  - Valida se a atualização de estado respeita o intervalo de tempo (`deltaTime`) fornecido.
- **Setters**:
  - Confirma se os métodos `setVelocity`, `setGravity` e `setForce` atualizam corretamente os atributos.
- **Exceção para Massa Zero**:
  - Garante que a criação de um objeto `Physics` com massa zero lança a exceção apropriada.

  ### 💻 Exemplo de Teste
Abaixo está um exemplo real de como os testes foram implementados. Este teste verifica se o construtor da classe `Physics` inicializa corretamente seus atributos:

```cpp
suite.addTest("Physics Constructor Test", []() {
    Physics physics(Vector2D(0, -9.8), 1.0);
    return vectorAlmostEqual(physics.getGravity(), Vector2D(0, -9.8)) &&
           almostEqual(physics.getMass(), 1.0) &&
           vectorAlmostEqual(physics.getVelocity(), Vector2D(0, 0));
});

Cria um objeto Physics com gravidade Vector2D(0, -9.8) e massa 1.0.
Verifica se os atributos gravity, mass e velocity são configurados corretamente.
Resultado Esperado:
A gravidade deve ser igual a Vector2D(0, -9.8).
A massa deve ser 1.0.
A velocidade inicial deve ser Vector2D(0, 0)

## ✅ Conclusão

- **Eficiência**:
  - A abordagem manual foi suficiente para validar o comportamento esperado da classe `Physics` em todos os cenários principais.
- **Adequação**:
  - Como os testes eram limitados em quantidade e escopo, utilizar um framework teria adicionado complexidade desnecessária.
- **Facilidade de Expansão**:
  - O sistema de testes manuais pode ser facilmente estendido para cobrir novos casos ou classes no futuro.

Essa solução simples e direta permitiu manter o projeto leve e funcional, sem comprometer a confiabilidade do código.


Link para o Video: 


# RELATORIO 05 :# Aprendendo uma Nova Linguagem e Implementando um Jogo

## 🌟 A Dificuldade na Aprendizagem de uma Nova Linguagem

Aprender uma nova linguagem vai além de memorizar comandos ou sintaxes. É necessário compreender os paradigmas que ela segue (orientação a objetos, funcional, procedural, etc.) e as ferramentas específicas que ela oferece. Por exemplo:

- Em C++, lidar com gestão de memória manual e o uso de ponteiros pode ser desafiador, especialmente para programadores acostumados a linguagens de mais alto nível como Python ou JavaScript.
- Além disso, integrar bibliotecas externas, como a SDL (Simple DirectMedia Layer), exige não apenas o domínio da linguagem, mas também um entendimento profundo das APIs que estão sendo utilizadas.

## 🎮 A Dificuldade de Implementar um Jogo

O desenvolvimento de um jogo combina lógica, criatividade e programação avançada. Alguns desafios comuns incluem:

- **Gestão de Recursos**:
  Gerenciar texturas, sons e outros ativos de forma eficiente é fundamental. Veja um exemplo de como texturas são carregadas e armazenadas em cache utilizando SDL:

    ```cpp
    std::shared_ptr<ITexture> SDLTexture::loadTexture(const std::string& filePath) {
        auto it = textureCache.find(filePath);
        if (it != textureCache.end()) {
            return it->second;
        }

        SDL_Surface* surface = IMG_Load(filePath.c_str());
        if (!surface) {
            std::cerr << "Unable to load image " << filePath << "! SDL_image Error: " << IMG_GetError() << std::endl;
            return nullptr;
        }

        SDL_Texture* newTexture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);

        if (!newTexture) {
            std::cerr << "Unable to create texture from " << filePath << "! SDL Error: " << SDL_GetError() << std::endl;
            return nullptr;
        }

        auto texture = std::make_shared<SDLTexture>(renderer);
        texture->texture = newTexture;
        textureCache[filePath] = texture;

        return texture;
    }
    ```

    Este exemplo mostra como texturas são armazenadas em cache para evitar carregamentos redundantes e economizar recursos.

- **Sistemas de Renderização**:
  Configurar um pipeline de renderização para exibir objetos na tela exige atenção a detalhes técnicos, como posições, tamanhos e interações.

- **Estruturas de Jogo**:
  Implementar sistemas como gerenciamento de estados (menu, jogo ativo, pausa) e eventos exige uma arquitetura clara e organizada.

## 🛠️ Estratégias para Superar os Desafios

1. **Dividir para Conquistar**:
   - Comece implementando pequenos módulos antes de abordar sistemas mais complexos. Por exemplo, implemente uma classe de gerenciamento de texturas antes de criar animações.

2. **Explorar Documentação e Exemplos**:
   - Utilize a documentação oficial e exemplos práticos para entender como integrar bibliotecas como a SDL ao seu projeto.

3. **Iteração Contínua**:
   - Desenvolva versões básicas e, ao aprender mais sobre a linguagem e os requisitos do jogo, refine e expanda as funcionalidades.

4. **Aprender com Erros**:
   - Debugging será seu melhor aliado. Cada erro enfrentado é uma oportunidade de compreender melhor a linguagem e os sistemas envolvidos.

## 🚀 Conclusão

Embora aprender uma nova linguagem e desenvolver um jogo sejam tarefas desafiadoras, elas são altamente recompensadoras. Funcionalidades como o gerenciamento de texturas, mostrado no exemplo acima, são marcos significativos nesse processo. Superar esses desafios expande suas habilidades técnicas e aumenta sua capacidade de resolver problemas complexos, essenciais para o sucesso em qualquer projeto de tecnologia.

Link para o Video: 

