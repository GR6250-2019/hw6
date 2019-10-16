# hw6

The purpose of this homework is to use Excel to explore pertubations of the standard normal distribution.
As Richard Hamming said, "The purpose of computing is insight, not numbers."

The Kolmogorov formula for infinitely divisible distributions shows how to compute the cumulants
given the parameters $\gamma$, a number, and $G$, an increasing function.
The first cumulant is $\gamma$ and the second and higher order cumulants are
$\kappa_n = \int_{-\infty}^\infty x^{n-2}\,dG(x)$.

If $X$ is standard normal, then $G(x) = 1(x \ge 0)$ and $dG$ is a delta function at 0.
$\kappa_2 = 1$ and all higher order cumulants are 0.

If $X$ is a standard normal plus a Poisson random variable then $G$ has another step
at a point not equal to 0 and the cumulant no longer converges.

In this homework we look for a parameterization that has a smooth curve. You need to
explore values for the parameters that do converge: $\alpha$, $a$, and $b$.

The curve $f_\alpha(x) = x^\alpha$ has derivative 0 at $x = 0$ if $\alpha > 1$.

The curve $f_{\alpha,a,b}(x) = x^\alpha b/a^\alpha$ has derivative 0 at $x = 0$ if $\alpha > 1$
and $f_{\alpha,a,b}(a) = b$.

We want to look at shifting this function back by $a$ and adding the
standard normal that keeps the variance (second cumulant) equal to
1: $G(x) = f_{\alpha,a,b}(x + a) 1(-a < x < 0) + (1 - b)1(x \ge 0)$.
It is 0 for $x < a$, smoothly increases to $b$ at $x = 0$, then jumps
to 1 for $x\ge0$.

You should plot this and note how it is a pertubation of the standard normal distribution.


