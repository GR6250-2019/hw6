# hw6

The purpose of this homework is to use Excel to explore pertubations of the standard normal distribution.
As Richard Hamming said, "The purpose of computing is insight, not numbers."

The Kolmogorov formula for infinitely divisible distributions shows how to compute the cumulants
given the parameters $\gamma$, a number, and $G$, an increasing function.
The first cumulant is $\gamma$ and the second and higher order cumulants are
$\kappa_n = \int_{-\infty}^\infty x^{n-2}\,dG(x)$.

If $X$ is standard normal, then $G(x) = 1(x \ge 0)$ is a step function at 0 and $dG$ is a delta function at 0.
$\kappa_2 = 1$ and all higher order cumulants are 0.

If $X$ is a standard normal plus a Poisson random variable then $G$ has another step
at a point not equal to 0 and the cumulant no longer converges.

In this homework we look for a parameterization that has a smooth curve. You need to
explore values for the parameters that do converge: $\alpha$, $a$, and $b$.

The curve $f_\alpha(x) = x^\alpha$ has derivative 0 at $x = 0$ if $\alpha > 1$.

The curve $f_{\alpha,a,b}(x) = x^\alpha b/a^\alpha$ has derivative 0 at $x = 0$ if $\alpha > 1$
and $f_{\alpha,a,b}(a) = b$.

We want to look at $G(x) = f_{\alpha,a,b}(x + a) 1(-a < x < 0) + (1 - b)1(x \ge 0)$.
It is 0 for $x < a$, smoothly increases to $b$ at $x = 0$, then jumps to 1 for $x\ge0$.

You should plot this and note how it is a pertubation of the standard normal distribution.

We have $dG(x) = ((x + a)^{\alpha - 1} \alpha b/a^\alpha 1_{[-a,0)}(x) + (1 - b) \delta_0(x))\,dx$

\begin{align*}
\int_{-a}^0 x^{n-2} (x + a)^{\alpha - 1} \, dx
&= \int_{a}^0 (-x)^{n-2} (-x + a)^{\alpha - 1} \, (-dx) \\
&= (-1)^{n-2} \int_0^a x^{n-2} (-x + a)^{\alpha - 1} \, dx \\
&= (-1)^{n-2} \int_0^1 (ax)^{n-2} (-ax + a)^{\alpha - 1} a\, dx \\
&= (-1)^{n-2} a^{n-1 + \alpha - 1}\int_0^1 x^{n-2} (1 - x)^{\alpha - 1} \, dx \\
&= (-1)^{n-2} a^{n-2} + \alpha}B(n-1,\alpha) \\
\end{align*}
where $B(\alpha,\beta) = \Gamma(\alpha)\Gamma(\beta)/\Gamma(\alpha + \beta)$ is the Beta function
and $\Gamma(\alpha) = \int_0^\infty x^{\alpha-1} e^{-x}\,dx$ is the Gamma function.
If $\alpha$ is a positive integer then $\Gamma(\alpha) = (\alpha - 1)!$.
This can be seen from the fact $\Gamma(0) = 1$ and $\Gamma(\alpha + 1) = \alpha\Gamma(\alpha)$.

This shows the second cumulant is $\kappa_2 = b\alpha B(1,\alpha) + (1 - b) = 1$
since $B(1,\alpha) = \Gamma(1)\Gamma(\alpha)/\Gamma(\alpha + 1) = 1/\alpha$.
But we already know that since $\kappa_2 = \int_{-\infty}^\infty\,dG = G(\infty) - G(-\infty) = 1$.

For $n > 2$ we have $\kappa_n = \alpha (-a)^{n - 2} b B(n - 1,\alpha)$.
We have the recurrence $\kappa_{n+1} = -\kappa_n a(n - 1)/(n - 1 + alpha)$.


## Hermite Polynomials

$H_n(x) = (-1)^{n} \phi(x)^{-1}(d/dx)^n \phi(x)$, where $\phi(x) = exp(-x^2/2)$.


$H_n(0) = (-1)^{n/2} (n-1)!!$ for $n$ even.

$n!! = 2^{n/2} (n/2)!$ for $n$ even.
