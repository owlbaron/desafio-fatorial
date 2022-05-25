# tinyexpr com fatorial (!)

Esse projeto é um "fork" do projeto [tinyexpr](https://github.com/codeplea/tinyexpr) feito no curso de Ciência da computação na aula de compiladores. O desafio é adicionar o calculo de fatorial através do simbolo "!".

## Como rodar

É só rodar o `make`:

```
make
```

e depois rodar o programa:

```
./main
```

Se precisar limpar os arquivos gerados use o `make clean`.

## Alterações

Adicionei o token "!" no lexer:

```
case '!': s->type = TOK_INFIX; s->function = fac; break;
```

Implementei a função de parsing:

```
static te_expr *factorial(state *s) {
    /* <factorial>     =   <base> {("!") <base>} */
    te_expr *ret = base(s);
  
    while (s->type == TOK_INFIX && (s->function == fac)) {
        te_fun2 t = s->function;
        next_token(s);
        ret = NEW_EXPR(TE_FUNCTION1 | TE_FLAG_PURE, ret);
        ret->function = t;
    }

    return ret;
}
```

Referenciei no parser descendente recursivo que já existia:

```
static te_expr *power(state *s) {
    /* <power>     =    {("-" | "+")} <factorial> */
    int sign = 1;
    while (s->type == TOK_INFIX && (s->function == add || s->function == sub)) {
        if (s->function == sub) sign = -sign;
        next_token(s);
    }

    te_expr *ret;

    if (sign == 1) {
        ret = factorial(s);
    } else {
        ret = NEW_EXPR(TE_FUNCTION1 | TE_FLAG_PURE, factorial(s));
        ret->function = negate;
    }

    return ret;
}
```

## Nova gramatica

```
<list>      =    <expr> {"," <expr>}
<expr>      =    <term> {("+" | "-") <term>}
<term>      =    <factor> {("*" | "/" | "%") <factor>}
<factor>    =    <power> {"^" <power>}
<power>     =    {("-" | "+")} <factorial>
<factorial>     =   <base> {("!") <base>}
<base>      =    <constant>
               | <variable>
               | <function-0> {"(" ")"}
               | <function-1> <power>
               | <function-X> "(" <expr> {"," <expr>} ")"
               | "(" <list> ")"
```
