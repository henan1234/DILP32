This is the boids program from the Microsoft DirectX5
final release. I've made it into a MSVC 5.0 project,
and added some comments. If you'd like to take on a challenge,
then rewrite the boids/sphere rendering to use another, more compact
form of rendering primitive other than a triangle list, such as a
triangle fan or triangle strip.

Also make special note of how state changes are handled, for example
around the rendering of the sphere.

Finally, if you've programmed D3D before, notice that boids uses a 
simpler method of creating the back and z buffer for full-screen
than was seen in previous SDK samples. This method is a lot simpler,
especially when you have to restore surfaces.

I'd be interested in observations, suggestions, etc. so feel free
to contact me at the address below.

Finally, I'm frequently asked what's the best way to learn D3D.
The problem is that they keep changing it. All the books that are
out there either focus on Retained Mode (which I find doesn't
satisfy my need for total control) or, if they do touch on
Immediate Mode, are hopelessly out of date. There are no books that
I *recommend*. You can check on my web site to see what I do think
of the current crop of books. If you're interesting in learning more
about how to program in 3D, I'd suggest some of the OpenGL books out
there. The functionality of D3DIM is similar to OpenGL, and the OpenGL
books are quite clear.

The best way of learning D3D is still to dissassemble the SDK
examples, ask lots of questions (try the rec.games.programmer newsgroup).
I'll make a stab at trying to answer questions, but don't hold
your breath, since I don't program in D3D that much. Remember, I'm not
a Microsoft employee, I run a 3D graphics consulting company, and time I spend
helping folks is time that I don't spend on paying projects.

Above all, don't be afraid to try things, look stupid (works for me),
ask questions, and steal code from other folks. Remember, this is supposed
to be fun. It's a big subject and it'll take a while to understand what's
going on, so take all the help you can get. Good luck!

Ron Fosner
ron@directx.com

Data Visualization
42 Chestnut St.
Hopkinton MA 01748
www.directx.com