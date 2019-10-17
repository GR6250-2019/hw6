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

We have $dG(x) = ((x + a)^{\alpha - 1} b/a^{\alpha - 1} + (1 - b) \delta_0(x))\,dx$

\begin{align*}
\int_{-a}^0 x^{n-2} (x + a)^{\alpha - 1} \, dx
&= \int_{a}^0 (-x)^{n-2} (-x + a)^{\alpha - 1} \, (-dx) \\
&= (-1)^{n-2} \int_0^a x^{n-2} (-x + a)^{\alpha - 1} \, dx \\
&= (-1)^{n-2} \int_0^1 (ax)^{n-2} (-ax + a)^{\alpha - 1} a\, dx \\
&= (-1)^{n-2} a^{n-2 + 2}\int_0^1 x^{n-2} (1 - x)^{\alpha - 1} \, dx \\
&= (-1)^{n-2} a^{n}B(n-1,\alpha) \\
\end{align*}
where $B(a,b) = \Gamma(a)\Gamma(b)/\Gamma(a + b)$ is the Beta function
and $\Gamma(a) = \int_0^\infty x^{a-1} e^{-x}\,dx$ is the Gamma function.
If $a$ is a positive integer then $\Gamma(a) = (a - 1)!$.


