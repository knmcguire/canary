# ros2_canary

Simple ROS 2 packages meant to be a canary for the CI and Build farm status

- `canary` — metapackage.
- `canary_cpp` — C++ "hello world" node (`tweet_publisher`) that publishes the string `"tweet"` on `/chatter` every second.

## Build farm status
Rdev: [![Build Status](https://build.ros2.org/buildStatus/icon?job=Rdev__canary__ubuntu_resolute_amd64)](https://build.ros2.org/view/Rdev/job/Rdev__canary__ubuntu_resolute_amd64/)

##  Local build

For testing out the packages, we use [pixi](https://pixi.sh).

```
pixi run build
```

## Run

After running `pixi shell` in your terminal:

```
ros2 run canary_cpp tweet_publisher (also sourced with pixi)
```

Check it's working in another terminal:

```
ros2 topic echo /chatter
```

## Test

```
pixi run test
pixi run test-result
```

<!-- CANARY_TIMESTAMP:START -->
_Canary heartbeat: 2026-09-02 17:12:16 UTC_
<!-- CANARY_TIMESTAMP:END -->
