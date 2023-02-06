-- Position Based Dynamics --
	- Abstract -
* Position based dynamics is a method of calculating softbody physics that assigns velocity and acceleration to each individual vertex of a mesh.
* Each mesh is uses the mass and volume of the assigned mesh and the normal of bounding boxes to calculate where each individual vertex of the mesh should position themselves.

	- Algorithm -
* (1) forall vertices i
  (2)   initialize xi = x0, vi = v0, wi = 1/mi
  (3) endfor
  (4) loop
  (5)   forall vertices i do vi ← vi +∆twifext(xi)
  (6)   dampVelocities(v1,...,vN)
  (7)   forall vertices i do pi ← xi +∆tvi
  (8)   forall vertices i do generateCollisionConstraints(xi → pi)
  (9)   loop solverIterations times
  (10)    projectConstraints(C1,...,CM+Mcoll ,p1,...,pN)
  (11)  endloop
  (12)  forall vertices i
  (13)     vi ← (pi −xi)/∆t
  (14)     xi ← pi
  (15)   endfor
  (16)   velocityUpdate(v1,...,vN)
  (17) endloop

	- Calculating Pressure -
* Softbody meshes would be inflated using a version of the Ideal Gas Law (PV=nRT).
	- P = Pressure
	- V = Volume
	- R = Constant
	- n = Number of Moles.
* Pressure is calculated with P = (nRT)/V.


