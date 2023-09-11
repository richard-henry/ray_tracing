CC = g++
CFLAGS = -I /home/henry/study/ray_tracing/1/include/
#虚路径
VPATH = 1_image 2_vec3 3_rays 4_sphere 5_surface 6_antialiasing 7_diffuse 8_metal 9_dialectric 10_camera

all: image vec3 rays sphere surface hitsurface antialiasing diffuse metal dialectric camera

image: 1_image.cpp
	cd 1_image/ && $(CC) $(CFLAGS) -o image 1_image.cpp

vec3: 2_vec3.cpp
	cd 2_vec3/ && $(CC) $(CFLAGS) -o vec3 2_vec3.cpp

rays: 3_rays.cpp
	cd 3_rays/ && $(CC) $(CFLAGS) -o rays 3_rays.cpp

sphere: sphere.cpp
	cd 4_sphere/ && $(CC) $(CFLAGS) -o sphere sphere.cpp

surface: surface.cpp
	cd 5_surface/ && $(CC) $(CFLAGS) -o surface surface.cpp

hitsurface: hitsurface.cpp
	cd 5_surface/ && $(CC) $(CFLAGS) -o hitsurface hitsurface.cpp

antialiasing: antialiasing.cpp
	cd 6_antialiasing/ && $(CC) $(CFLAGS) -o antialiasing antialiasing.cpp

diffuse: diffuse.cpp
	cd 7_diffuse/ && $(CC) $(CFLAGS) -o diffuse diffuse.cpp

metal: metal.cpp
	cd 8_metal/ && $(CC) $(CFLAGS) -o metal metal.cpp

dialectric: dialectric.cpp
	cd 9_dialectric/ && $(CC) $(CFLAGS) -o dialectric dialectric.cpp

camera: camera.cpp
	cd 10_camera/ && $(CC) $(CFLAGS) -o camera camera.cpp