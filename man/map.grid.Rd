\name{map.grid}
\alias{map.grid}
\title{
  Draw a latitude/longitude grid on a projected map
}
\description{
  Draws a grid on an existing map.
}
\usage{
map.grid(lim,nx=9,ny=9,labels=TRUE,pretty=TRUE,cex,col,lty,font,...)
}
\arguments{
  \item{lim}{a vector of 4 numbers specifying
    limits: \code{c(lon.low, lon.high, lat.low, lat.high)}.
    \code{lim} can also be a list with a component named \code{range}, such
    as the result of \code{map}, from which limits are taken.
  }
  \item{nx,ny}{the desired number of equally-spaced longitude and
    latitude lines}
  \item{labels}{logical to indicate if grid lines should be labeled with
    longitude/latitude values.}
  \item{pretty}{If \code{TRUE}, grid lines will be placed at round numbers.}
  \item{cex}{}
  \item{col}{}
  \item{lty}{}
  \item{font}{}
  \item{...}{additional arguments passed to \code{lines} and
    \code{text}, e.g.  \code{col} to change the color of the grid and
    \code{lty} to change the line type.}
}
\value{
  Equally-spaced lines of constant longitude and lines of constant
  latitude are superimposed on the current map, using the current projection.
  These lines will appear curved under most projections, and give an idea of
  how the projection works.
}
\seealso{\code{\link{map}}}
\examples{
library(maps)
m <- map("usa",plot=FALSE)
map("usa",project="albers",par=c(39,45))
map.grid(m)

# get unprojected world limits
m <- map('world',plot=FALSE)

# center on NYC
map('world',proj='azequalarea',orient=c(41,-74,0))
map.grid(m,col=2)
points(mapproject(list(y=41,x=-74)),col=3,pch="x",cex=2)

map('world',proj='orth',orient=c(41,-74,0))
map.grid(m,col=2,nx=6,ny=5,label=FALSE,lty=2)
points(mapproject(list(y=41,x=-74)),col=3,pch="x",cex=2)

# center on Auckland
map('world',proj='orth',orient=c(-36.92,174.6,0))
map.grid(m,col=2,label=FALSE,lty=2)
points(mapproject(list(y=-36.92,x=174.6)),col=3,pch="x",cex=2)

m <- map('nz')
# center on Auckland
map('nz',proj='azequalarea',orient=c(-36.92,174.6,0))
points(mapproject(list(y=-36.92,x=174.6)),col=3,pch="x",cex=2)
map.grid(m,col=2)
}
\keyword{aplot}
