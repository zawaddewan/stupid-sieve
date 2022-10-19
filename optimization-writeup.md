# Optimization Write up
Hello, I wrote this to help make my code, which is really unintuitive at first glance, make more sense

## Size approximation
Using a bit of wikipedia and desmos, I learned about the prime counting function, π(x).
π(x) returns the number of primes less than or equal to x. Due to the prime-number theorem, this function is asymptotic to x/ln(x)

If you plug in pn, then π(pn) = n, since there are n primes that are less than or equal to the nth prime. Due to the aforementioned asymptote, π(pn) ~ pn/ln(pn)
Do some rearranging, and you get that pn ~ nln(pn). We can then recursively define pn. 
Nesting log twice is good enough for a tight approximation, so we can say π(x) ~ nln(nln(n)). This approximation overshoots for n >= 6.
Doing some desmos got me nln(nln(nln(n))) - n, which is closer for larger n but only overshoots for n >= 28.
Lee gave me a very stupid stackoverflow french math approximation, which is n(ln(n) + ln(ln(n)) - 1 + ((ln(ln(n)) - 2) / ln(n))).
I have no idea how this one works, but overshoots for n >= 270963 with a very low margin of error. Adding 217 to the french approximation makes it overshoot for all n, although it is wildly off for smaller n due to adding that constant term.

## What the hell is going on in that first while loop
The less numbers that are checked, the faster the program will run.
The first size change I made was to get rid of even numbers, which is self explanatory. What follows after multiples 2 is multiples of 3, but this is can be either a little or a lot more complicated depending on the implementation.
I was going to print the first 100 numbers that are neither even nor multiples of 3, but thats a lot of space, so they're in the text file list.txt and [this hastebin](https://hastebin.com/ixuxesewun.yaml), in the order (number, index).

To map a list index to the corresponding number of this magic list, you can do 3*index + 1 + index%2.

To go from one multiple to the next, you compute the original number + (index + index%2)(-1)^(index%2) and add that to your index.

To go map a number back to its index, you can do (number - 1 - index%2) / 3. 

There's a problem though, you need to have the original index. Luckily, it doesn't matter in this case, because a pattern of the list is that any perfect square ends up on an even index, which means we can ignore the index%2 term.
This means that if we want to take a perfect square and get back its index, we can do (number - 1) / 3.

We can take this further. If we want the index of the square of a number for which we already have an index, we can simply substitute "number" for "(3\*index + 1 + index%2)^2"

For the sake of brevity, I'll let k = index%2 and I'll abbreviate index as i.

Now we have ((3i+1+k)^2 - 1)) / 3. If we expand the square we get (9i^2 + 6ik + 6i + k^2 + 2k + 1 - 1) / 3. Since k can only be 1 or 0 (anything mod 2 is either 1 or 0), we know k^2 = k.

Cleaning up -> (9i^2 + 6ik + 6i + 3k) / 3 -> 3i^2 + 2ik + 2i + k. This gives us the index of the square of a number within our magic list, provided we know the index of that number.

Lastly, doing modulo over and over is pretty slow. Luckily, this term is constantly oscillating between 0 and 1, we can substitute any modulo by 2 with using the bitwise ! operator. Doing !0 gives us 1, and doing !1 gives us 0. Setting k to 1 and then doing k = !k each loop helps us save time.

## Funky second while loop

I needed a way to speed up checking if each number was prime or composite after finishing sieving up to the square root of my size.
Instead of running an if statement, I could try and map the value in each array slot to 0 for composites and 1 for primes. 
Right now, though, composites have 'a' inside their slot and primes have 0. Using the ! operator we can map any non-zero integer to 0 and 0 to 1, which lets us track primes without conditionals.
