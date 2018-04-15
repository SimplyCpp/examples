## Implementações variadas à regra de Horner (Horner’s Rules)
###### por Fabio Galuppo ([@FabioGaluppo](https://twitter.com/fabiogaluppo))

 **_Variadic functions_** são funções que aceitam um número arbitrário de argumentos. No **C++**, existe uma forma dinâmica de resolução deste tipo de função herdada do **C** através de [**_variadic arguments_**](http://en.cppreference.com/w/cpp/language/variadic_arguments). Além de outra, introduzida no **C++** moderno, que é de resolução estática e baseada em <_templates_, denominada de [_variadic templates_](http://en.cppreference.com/w/cpp/language/parameter_pack).

Neste post, o objetivo é mostrar a implementação do método de Horner utilizando estas duas abordagens com _variadic_, uma que é resolvida em tempo de execução (_variadic arguments_) e outra em tempo de compilação (_variadic templates_).

O [método de Horner](https://pt.wikipedia.org/wiki/Esquema_de_Horner) é um algoritmo para transformar um polinômio em um monômio e deixá-lo computacionalmente eficiente. Por exemplo, trocando potência por um encadeamento de multiplicações, onde pode se explorar a caracteristicas de operações similares a [SAXPY](https://en.wikipedia.org/wiki/Basic_Linear_Algebra_Subprograms#Level_1). Um breve exemplo deste esquema é encontrado em [Horner’s Rule](http://mathworld.wolfram.com/HornersRule.html") na [Wolfram MathWorld](http://mathworld.wolfram.com/). Consistindo na transformação do polinômio:

![polynomial](https://github.com/SimplyCpp/examples/raw/master/horner_method_and_variadic/resources/polynomial.png)

Em:

![monomial](https://github.com/SimplyCpp/examples/raw/master/horner_method_and_variadic/resources/monomial.png)

**Implementação com _variadic arguments_**

No **C++**, basta utilizar o header [**cstdarg**](http://www.cplusplus.com/reference/cstdarg/), que possui o tipo [**va_list**](http://www.cplusplus.com/reference/cstdarg/va_list/) e as macros: [**va_start**](http://www.cplusplus.com/reference/cstdarg/va_start/), [**va_arg**](http://www.cplusplus.com/reference/cstdarg/va_arg/) e [**va_end**](http://www.cplusplus.com/reference/cstdarg/va_end/). Que servem para identificar o ponto dos argumentos _variadic_, bem como iterá-los. Em essência, é muito simples utilizar estes recursos, conforme o código do exemplo a seguir.  Note que nesta implementação o polinômio de maior grau está a esquerda (terceiro argumento) e o primeiro argumento é a quantidade de argumentos da função _variadic_:

```cpp
/* variadic functions */
#include <cstdarg>

//an * x^n + ... + a2 * x^2 + a1 * x^1 + a0
//fold right: (x * (x * ((argn * x) + argm) + argo) ...)
template <typename T>
T va_horner_method(int n, T x, T argn, T argm, ...)
{
	T result = axpy(x, argn, argm);
	va_list args;
	va_start(args, argm);
	for (int i = 3; i < n; ++i)
	{
		T arg = va_arg(args, T);
		result = axpy(x, result, arg);
	}
	va_end(args);
	return result;
}
/* variadic functions */
```

Apesar da simplicidade, é necessário ter o mesmo tipo de cuidado que se têm quando se manipula ponteiros. Por exemplo, se você iterar além do número de elementos fornecidos, poderá obter um comportamento não definido e/ou ler dados inválidos.

**Implementação com _variadic templates_**

No **C++** moderno, uma ampliação no mecanismo de _templates_ foi introduzido para suportar um número variável de argumentos parametrizáveis. Isto é resolvido em tempo de compilação. Neste caso, a expansão deste argumentos podem ser resolvidos por recursividade, demandando uma especialização parcial como caso base. No código abaixo isto deverá ficar um pouco mais claro:

```cpp
/* variadic templates */
template <typename T, typename... Ts>
struct Horner
{
	constexpr static T apply(T x, T arg0, Ts... args)
	{
		return axpy(x, Horner<Ts...>::apply(x, args...), arg0);
	}
};

template <typename T>
struct Horner<T, T>
{
	constexpr static T apply(T x, T arg0, T arg1)
	{
		return axpy(x, arg1, arg0);
	}
};
/* variadic templates */
```

Veja as seguintes chamadas:

```cpp
double a = Horner<double, double>::apply(1.0, 2.0, 3.0);
double b = Horner<double, double, double>::apply(1.0, 2.0, 3.0, 4.0);
```

Na primeira chamada, somente o método apply do caso base do tipo **Horner** será invocado, onde apenas 2 argumentos de _template_ e 3 argumentos no método são requisitos para isso. Na segunda chamada, ocorrerá a seguinte expansão de chamadas:

```cpp
axpy(1.0, axpy(1.0, 4.0, 3.0), 2.0);
```

Para obtermos o beneficio da dedução dos argumentos dos _templates_, a função _helper_ abaixo é fornecida:

```cpp
/* variadic templates */
//a0 + a1 * x^1  + a2 * x^2 + ... + an * x^n
//fold left: (x * (x * ((argn * x) + argm) + argo) ...)
template <typename T, typename... Ts>
constexpr inline T horner_method(T x, Ts... args)
{
	return Horner<Ts...>::apply(x, args...);
}
/* variadic templates */
```

Logo uma chamada com 5 argumentos (e 4 argumentos _templates_) é feita desta maneira:

```cpp
double c = horner_method(1.0, 2.0, 3.0, 4.0, 5.0);
```

Possuindo uma expansão na forma:

```cpp
axpy(1.0, axpy(1.0, axpy(1.0, 5.0, 4.0), 3.0), 2.0);
```

Note que nesta implementação o polinômio de maior grau está a direita (último argumento). Mesmo sendo definido em termos de recursão, a implementação quando compilada em modo otimizado, eliminará as chamadas recursivas tornando tudo uma sequência inline, conforme demonstrado nas expansões anteriores. Dependendo da "agressividade" do otimizador uma expansão similar ao exemplo anterior se transforma em apenas uma única linha de código _assembly_:

![horner_inline](https://github.com/SimplyCpp/examples/raw/master/horner_method_and_variadic/resources/horner_inline.png)

###### Referências
http://en.cppreference.com/w/cpp/language/variadic_arguments

http://en.cppreference.com/w/cpp/language/parameter_pack

###### Fonte
https://github.com/SimplyCpp/examples/tree/master/horner_method_and_variadic/src/horner_method_program.cpp