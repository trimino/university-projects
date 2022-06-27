echo 'Removing turtle_race container'
docker rm calc

echo 'Removing turtle_race_build image'
docker rmi calc_build

echo 'Removing all images with <none> tag'
docker rmi $(docker images -f 'dangling=true' -q)
