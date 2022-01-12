\name{mapproject}
\alias{mapproject}
\title{
  Apply a Map Projection
}
\description{
  Converts latitude and longitude into projected coordinates.
}
\usage{
mapproject(x, y, projection="", parameters=NULL, orientation=NULL)
}
\arguments{
\item{x,y}{
two vectors giving longitude and latitude coordinates
of points on the earth's surface to be projected.
A list containing components named \code{x} and \code{y}, giving the
coordinates of the points to be projected may also be given.
Missing values (\code{NA}s) are allowed.
The coordinate system is degrees of longitude east of Greenwich
(so the USA is bounded by negative longitudes) and degrees
north of the equator.
}
\item{projection}{
optional character string that names a map projection to
use.  If the string is \code{""} then the previous projection is used,
with parameters modified by the next two arguments.
}
\item{parameters}{
optional numeric vector of parameters for use with the
\code{projection} argument.
This argument is optional only in the sense that certain
projections do not require additional parameters.
If a projection does require additional parameters, these
must be given in the \code{parameters} argument.
}
\item{orientation}{
  An optional vector \code{c(latitude,longitude,rotation)} which describes
  where the "North Pole" should be when computing the projection.
  Normally this is \code{c(90,0)}, which is appropriate for 
  cylindrical and conic projections.  For a planar projection, you should
  set it to the desired point of tangency.
  The third value is a clockwise rotation (in degrees), which defaults
  to the midrange of the longitude coordinates in the map.
  This means that two maps plotted with their own default orientation
  may not line up.  To avoid this, you should not specify a projection
  twice but rather default to the previous projection using
  \code{projection=""}.  See the examples.
}}
\value{
list with components
named \code{x} and \code{y}, containing the projected coordinates.
\code{NA}s project to \code{NA}s.
Points deemed unprojectable (such as north of 80 degrees
latitude in the Mercator projection) are returned as \code{NA}.
Because of the ambiguity of the first two arguments, the other
arguments must be given by name.


Each time \code{mapproject} is called, it leaves on frame 0 the
dataset \code{.Last.projection}, which is a list with components \code{projection},
\code{parameters}, and \code{orientation} giving the arguments from the
call to \code{mapproject} or as constructed (for \code{orientation}).
Subsequent calls to \code{mapproject} will get missing information
from \code{.Last.projection}.
Since \code{map} uses \code{mapproject} to do its projections, calls to
\code{mapproject} after a call to \code{map} need not supply any arguments
other than the data.
}
\details{
Each standard projection is displayed with the Prime
Meridian (longitude 0) being a straight vertical line, along which North
is up.
The orientation of nonstandard projections is specified by
the three \code{parameters=c(lat,lon,rot)}.
Imagine a transparent gridded sphere around the globe.
First turn the overlay about the North Pole
so that the Prime Meridian (longitude 0)
of the overlay coincides with meridian \code{lon} on the globe.
Then tilt the North Pole of the
overlay along its Prime Meridian to latitude \code{lat} on the globe.
Finally again turn the
overlay about its "North Pole" so
that its Prime Meridian coincides with the previous position
of (the overlay) meridian \code{rot}.
Project the desired map in
the standard form appropriate to the overlay, but presenting
information from the underlying globe.


In the descriptions that follow each projection is shown as a
function call; if it requires parameters, these are shown as
arguments to the function.
The descriptions are grouped into families.


Equatorial projections centered on the Prime Meridian (longitude 0).
Parallels are straight horizontal lines.
\describe{
\item{mercator()}{equally spaced straight meridians, conformal, straight
   compass courses}
\item{sinusoidal()}{equally spaced parallels, equal-area, same
as \code{bonne(0)}}
\item{cylequalarea(lat0)}{equally spaced straight meridians,
   equal-area, true scale on \code{lat0}}
\item{cylindrical()}{central projection on
   tangent cylinder}
\item{rectangular(lat0)}{equally spaced parallels, equally
   spaced straight meridians, true scale on \code{lat0}}
\item{gall(lat0)}{parallels
   spaced stereographically on prime meridian, equally spaced straight
   meridians, true scale on \code{lat0}}
\item{mollweide()}{(homalographic) equal-area,
  hemisphere is a circle}
\item{gilbert()}{sphere conformally mapped on hemisphere and viewed orthographically}
}

Azimuthal projections centered on the North Pole. Parallels are
concentric circles. Meridians are equally spaced radial lines.
\describe{
\item{azequidistant()}{equally spaced parallels, true distances from pole}
\item{azequalarea()}{equal-area}
\item{gnomonic()}{central projection on tangent plane,
   straight great circles}
\item{perspective(dist)}{viewed along earth's axis \code{dist}
   earth radii from center of earth}
\item{orthographic()}{viewed from infinity}
\item{stereographic()}{conformal, projected from opposite pole}
\item{laue()}{\code{radius = tan(2 * colatitude)} used in xray crystallography}
\item{fisheye(n)}{stereographic seen through medium with refractive
  index \code{n}}
\item{newyorker(r)}{\code{radius = log(colatitude/r)} map from viewing
  pedestal of radius \code{r} degrees}
}

Polar conic projections symmetric about the Prime Meridian. Parallels
are segments of concentric circles. Except in the Bonne projection,
meridians are equally spaced radial lines orthogonal to the parallels.
\describe{
\item{conic(lat0)}{central projection on cone tangent at \code{lat0}}
\item{simpleconic(lat0,lat1)}{equally spaced parallels, true scale on \code{lat0} and \code{lat1}}
\item{lambert(lat0,lat1)}{conformal, true scale on \code{lat0} and \code{lat1}}
\item{albers(lat0,lat1)}{equal-area, true scale on \code{lat0} and \code{lat1}}
\item{bonne(lat0)}{equally spaced parallels, equal-area, parallel \code{lat0}
   developed from tangent cone}
}

Projections with bilateral symmetry about the Prime Meridian and the equator. 
\describe{
\item{polyconic()}{parallels developed from tangent
   cones, equally spaced along Prime Meridian}
\item{aitoff()}{equal-area
   projection of globe onto 2-to-1 ellipse, based on \code{azequalarea}}
\item{lagrange()}{conformal, maps whole sphere into a circle}
\item{bicentric(lon0)}{points plotted at true azimuth from two centers on the
equator at longitudes \code{+lon0} and \code{-lon0}, great circles are 
straight lines (a stretched gnomonic projection)}
\item{elliptic(lon0)}{points are    
   plotted at true distance from two centers on the equator at longitudes
   \code{+lon0} and \code{-lon0}}
\item{globular()}{hemisphere is circle, circular arc meridians
   equally spaced on equator, circular arc parallels equally spaced on 0-
   and 90-degree meridians}
\item{vandergrinten()}{sphere is circle, meridians as      
  in \code{globular}, circular arc parallels resemble \code{mercator}}
\item{eisenlohr()}{conformal with no singularities, shaped like polyconic}
}

Doubly periodic conformal projections.
\describe{
  \item{guyou}{W and E hemispheres are square}
  \item{square}{world is square with Poles at diagonally opposite
    corners}
  \item{tetra}{map on tetrahedron with edge
    tangent to Prime Meridian at S Pole,
    unfolded into equilateral triangle}
  \item{hex}{world is hexagon centered
    on N Pole, N and S hemispheres are equilateral triangles}
}

Miscellaneous projections.
\describe{
\item{harrison(dist,angle)}{oblique   
   perspective from above the North Pole, \code{dist} earth radii from center of
   earth, looking along the Date Line \code{angle} degrees off vertical}
\item{trapezoidal(lat0,lat1)}{equally spaced parallels, straight meridians
   equally spaced along parallels, true scale at \code{lat0} and \code{lat1} on Prime
   Meridian}
 \item{lune(lat,angle)}{conformal, polar cap above latitude \code{lat}
   maps to convex lune with given \code{angle} at 90E and 90W}
}

Retroazimuthal projections. At every point the angle between vertical
and a straight line to "Mecca", latitude \code{lat0} on the prime meridian,  
is the true bearing of Mecca. 
\describe{
\item{mecca(lat0)}{equally spaced vertical meridians}
\item{homing(lat0)}{distances to Mecca are true}
}

Maps based on the spheroid. Of geodetic quality, these projections do
not make sense for tilted orientations. 
\describe{
\item{sp\_mercator()}{Mercator on the spheroid.}
\item{sp\_albers(lat0,lat1)}{Albers on the spheroid.}
}
} % end details
\references{
  Richard A. Becker, and Allan R. Wilks,
  "Maps in S",
  \emph{AT\&T Bell Laboratories Statistics Research Report, 1991.}
  \url{ https://web.archive.org/web/20070824013345/http://www.research.att.com/areas/stat/doc/93.2.ps}

  M. D. McIlroy,
  Documentation from the
  \emph{Tenth Edition UNIX Manual, Volume 1,}
  Saunders College Publishing, 1990.
}
\examples{
library(maps)
# Bonne equal-area projection with state abbreviations
map("state",proj='bonne', param=45)
data(state)
text(mapproject(state.center), state.abb)

# this does not work because the default orientations are different:
map("state",proj='bonne', param=45)
text(mapproject(state.center,proj='bonne',param=45),state.abb)

map("state",proj="albers",par=c(30,40))
map("state",par=c(20,50)) # another Albers projection

map("world",proj="gnomonic",orient=c(0,-100,0)) # example of orient
# see map.grid for more examples

# tests of projections added RSB 091101
projlist <- c("aitoff", "albers", "azequalarea", "azequidist", "bicentric",
 "bonne", "conic", "cylequalarea", "cylindrical", "eisenlohr", "elliptic",
 "fisheye", "gall", "gilbert", "guyou", "harrison", "hex", "homing",
 "lagrange", "lambert", "laue", "lune", "mercator", "mollweide", "newyorker",
 "orthographic", "perspective", "polyconic", "rectangular", "simpleconic",
 "sinusoidal", "tetra", "trapezoidal")
x <- seq(-100, 0, 10)
y <- seq(-45, 45, 10)
xy <- expand.grid(x=x, y=y)
pf <- c(0, 2, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 2, 0, 1, 0, 2, 0, 2,
 0, 0, 1, 0, 1, 0, 1, 2, 0, 0, 2)
res <- vector(mode="list", length=length(projlist))
for (i in seq(along=projlist)) {
 if (pf[i] == 0) res[[i]] <- mapproject(xy$x, xy$y, projlist[i])
 else if (pf[i] == 1) res[[i]] <- mapproject(xy$x, xy$y, projlist[i], 0)
 else res[[i]] <- mapproject(xy$x, xy$y, projlist[i], c(0,0))
}
names(res) <- projlist
lapply(res, function(p) rbind(p$x, p$y))
}
\keyword{dplot}
