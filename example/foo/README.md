# Concepts (From Boost.Hana docs)

# Monoid

Requires `plus` and `zero`

```cpp
plus(zero<M>(), x) == x                    // left zero
plus(x, zero<M>()) == x                    // right zero
plus(x, plus(y, z)) == plus(plus(x, y), z) // associativity
```

# Group

Requires `minus` or `negate`
Refines Monoid

```cpp
plus(x, negate(x)) == zero<G>() // right inverse
plus(negate(x), x) == zero<G>() // left inverse
```
