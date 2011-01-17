.First.lib <- function(lib, pkg) {
  library.dynam("mapproj", pkg, lib)
# RSB 110117 remove external reference NOTE to .map.range
  xx <- try(get(".map.range", env=globalenv()), silent=TRUE)
  if (class(xx) == "try-error")
    assign(".map.range", as.numeric(c(0, 1, 0, 1)), envir = globalenv())
}
