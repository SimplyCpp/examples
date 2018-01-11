## Handy Union
###### por Fabio Galuppo ([@FabioGaluppo](https://twitter.com/fabiogaluppo)) 

Desde os primórdios da linguagem C, os [**_union types_**](http://en.cppreference.com/w/cpp/language/union), ou simplesmente **_unions_** são tipos especiais que permitem dois ou mais membros do tipo dado (e não estáticos) compartilhem o mesmo endereço inicial e área da memória, ou seja, uma espécie de sobreposição num espaço da memória comum, onde o tamanho total desta área compartilhada é equivalente a do maior tipo especificado, ou seja, seu [`sizeof`](http://en.cppreference.com/w/cpp/language/sizeof).

Com **C++**, é possível fazer uso deste recurso de forma genérica, utilizando **_templates_**. Neste caso, apresento um tipo _helper_ genérico que denominei de `handy_union` por causa da praticidade oferecida por ele. Mas, o que de fato ele oferece? 

Abaixo o código integral do `handy_union` em **C++**:

```cpp
template<typename T>
struct handy_union final
{
	handy_union() = default;
	handy_union(const handy_union&) = default;
	handy_union& operator=(const handy_union&) = default;
	~handy_union() = default;
	
	handy_union(T value) : value(value) {}

	constexpr std::size_t size() const { return sizeof(T); }

	operator T() const { return value; }

	union
	{
		unsigned char bytes[sizeof(T)];
		T value;
	};
};
```

O `handy_union` foi criado para compartilhar ou ter uma sobreposição entre um determinado tipo instanciado pelo _template_ e um _array_ de _bytes_ com tamanho proporcional a quantidade de memória alocada estaticamente desta instância. É possível construir um `handy_union` com um valor indicado em seu construtor ou alterá-lo através do membro do tipo dado `value`, bem como, ler ou alterar cada byte através do membro do tipo dado `bytes`. Por exemplo, o uso e a consulta de uma instância com o tipo `unsigned int` compilado para **x86** ou **x64** produzirá o valor `true` na variável `is_true`:

```cpp
handy_union<unsigned int> x(0xFFEEDDCC);
bool is_true = (x.bytes[3] == 0xFF) && 
               (x.bytes[2] == 0xEE) && 
               (x.bytes[1] == 0xDD) &&
               (x.bytes[0] == 0xCC);
```

A praticidade se dá pelo fato de podermos preencher o objeto através do valor e manipular sua representação em _bytes_:

```cpp
handy_union<unsigned int> x;
x = 0xFFEEDDCC;
std::reverse(x.bytes, x.bytes + x.size());
```

Ou vice-versa:

```cpp
handy_union<unsigned int> x;
std::fill(x.bytes, x.bytes + x.size(), 0);
x.bytes[0] = 1;
```

A necessidade da criação do `handy_union` surgiu quando eu precisei passar valores arbitários, de tipos primitivos à estruturas complexas, em APIs de baixo nível, que aceitavam somente parâmetros em forma de _array_ de _bytes_, logo seria necessário algum tipo de serialização para essa tarefa. No entanto, por ter um recurso como os **_unions_** na linguagem, foi possível construir, de forma eficiente, essa flexibilidade de acesso ao tipo e sua representação física.

Se você precisar alternar entre os [_endianness_](https://en.wikipedia.org/wiki/Endianness) do objeto que está manipulando, isto também é possível, somente aplicar um `reverse` aos `bytes`, como mostrado no exemplo abaixo:

```cpp
handy_union<unsigned int> x;
x.value = 0x90AB12CD;	
	
//if the last byte from value is the first item in bytes then is little endian
bool is_little_endian = x.bytes[0] == 0xCD; 

std::cout.setf(std::ios::hex, std::ios::basefield);

std::cout << (is_little_endian ? "little" : "   big") << " endian: ";
for (size_t i = 0; i < x.size(); ++i)
	std::cout << static_cast<int>(x.bytes[i]) << " ";
std::cout << "\n";

//changing endianness
is_little_endian = !is_little_endian;
std::reverse(x.bytes, x.bytes + x.size());

std::cout << (is_little_endian ? "little" : "   big") << " endian: ";
for (size_t i = 0; i < x.size(); ++i)
	std::cout << static_cast<int>(x.bytes[i]) << " ";
std::cout << "\n";
	
std::cout.unsetf(std::ios::hex);

//Output in x86 or x64 systems:
//little endian: cd 12 ab 90
//   big endian: 90 ab 12 cd
```

###### Resultado da compilação e execução no g++ e no msvc (Visual C++)

![g++](https://github.com/SimplyCpp/examples/raw/master/handy_union/resources/handy_union_g%2B%2B.png)

![msvc](https://github.com/SimplyCpp/examples/raw/master/handy_union/resources/handy_union_cl.png)

###### _Zero-cost abstraction_

A abstração do `handy_union` é custo zero, ou seja, nada além do tamanho (`sizeof`) do tipo ocupa a memória. Podemos ver isso no _disassembly_ com o [Compiler Explorer](https://godbolt.org/) numa versão do código otimizado:

![disassembly](https://github.com/SimplyCpp/examples/raw/master/handy_union/resources/handy_union_disassembly.png)

Note a _zero-cost abstraction_ por duas relações na transformação do código para _assembly_:
1. Na linha 34 as operações com `sizeof` no código **C++** a esquerda equivale as linhas 19 e 20 do _assembly_ a direita, ambas com 4 _bytes_ cada.
2. As linhas 28 e 29 no código **C++** equivalem as linhas de 7 a 12 do _assembly_. As linhas 31 e 32 no código **C++** equivalem as linhas de 13 a 18 do _assembly_. Portanto, as mesmas instruções com uma pequena variação na ordem, mas sem discrepância na associação com os registradores.

###### Referência
http://en.cppreference.com/w/cpp/language/union

###### Fontes
https://github.com/SimplyCpp/examples/blob/master/handy_union/src/handy_union.hpp
https://github.com/SimplyCpp/examples/blob/master/handy_union/src/handy_union.t.cpp
