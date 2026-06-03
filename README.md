# romea_localisation_odo_plugin

`romea_localisation_odo_plugin` provides a ROS2 localisation plugin node that converts mobile base controller feedback into `romea_localisation_msgs` twist observations.

The plugin can consume either standard odometry messages or ROMEA mobile base kinematic measurements. It publishes a planar twist observation that can be fused by localisation filters.

## 1) Concept

The odometry localisation plugin is an observation producer. It does not estimate the robot pose by itself. It converts controller feedback into a 2D twist observation.

```mermaid
flowchart LR
  subgraph ros2_inputs["ROS2 input messages"]
    direction TB
    odom["vehicle_controller/odom<br/><br/>nav_msgs/msg/Odometry"]
    kinematic["vehicle_controller/kinematic<br/><br/>romea_mobile_base_msgs/msg/KinematicMeasureStamped"]
  end

  subgraph plugin_nodes["Localisation plugin node"]
    plugin["Odometry localisation plugin<br/><br/>build 2D twist observations"]
  end

  subgraph observation_msgs["romea_localisation_msgs"]
    twist["twist<br/><br/>romea_localisation_msgs/msg/ObservationTwist2DStamped"]
  end

  subgraph filters["Localisation filters"]
    filter["robot-to-world / robot-to-robot / robot-to-human localisation"]
  end

  odom -->|consume| plugin
  kinematic -->|consume| plugin
  plugin -->|publish| twist
  twist -->|fuse| filter

  classDef ros2 fill:#e8f2ff,stroke:#5b8ec7,color:#111,rx:6,ry:6
  classDef pluginStyle fill:#eaf7ea,stroke:#5c9f5c,color:#111,rx:6,ry:6
  classDef msg fill:#fff6d8,stroke:#c9a227,color:#111,rx:6,ry:6
  classDef filterStyle fill:#f1eaff,stroke:#8b6fc6,color:#111,rx:6,ry:6

  class odom,kinematic ros2
  class plugin pluginStyle
  class twist msg
  class filter filterStyle

  style ros2_inputs fill:#f6faff,stroke:#9abbe3,rx:6,ry:6
  style plugin_nodes fill:#f7fff7,stroke:#9ecf9e,rx:6,ry:6
  style observation_msgs fill:#fffaf0,stroke:#dec86b,rx:6,ry:6
  style filters fill:#faf7ff,stroke:#b8a4dd,rx:6,ry:6
```

Only one controller feedback source is used at runtime. The source is selected with the `controller_topic` parameter.

## 2) Provided Plugin

| Executable | Component plugin |
| --- | --- |
| `odo_localisation_plugin_node` | `romea::ros2::localisation::OdoPlugin` |

## 3) Input Topics

| Topic | Type | Use |
| --- | --- | --- |
| `vehicle_controller/odom` | `nav_msgs/msg/Odometry` | Standard odometry feedback, selected with `controller_topic: odom` |
| `vehicle_controller/kinematic` | `romea_mobile_base_msgs/msg/KinematicMeasureStamped` | ROMEA mobile base kinematic feedback, selected with `controller_topic: kinematic` |

The `kinematic` source is preferred when available because it is produced by ROMEA mobile base controllers and is intended to carry kinematic measurements with consistent uncertainty information.

## 4) Output Topics

| Topic | Type | Description |
| --- | --- | --- |
| `twist` | `romea_localisation_msgs/msg/ObservationTwist2DStamped` | Planar twist observation with covariance |

The observation contains longitudinal speed, lateral speed and yaw angular speed.

## 5) Parameters

| Parameter | Type | Default | Description |
| --- | --- | --- | --- |
| `controller_topic` | string | `kinematic` | Controller feedback source. Accepted values are `odom` and `kinematic` |
| `restamping` | bool | `false` | If true, observations are stamped with the node clock instead of the input message stamp |

## 6) Configuration and Run

Run the plugin with:

```bash
ros2 run romea_localisation_odo_plugin odo_localisation_plugin_node \
  --ros-args --params-file path/to/odo_localisation_plugin.yaml
```

Example parameter file using the ROMEA kinematic feedback:

```yaml
odo_localisation_plugin:
  ros__parameters:
    controller_topic: kinematic
    restamping: false
```

Example parameter file using standard odometry feedback:

```yaml
odo_localisation_plugin:
  ros__parameters:
    controller_topic: odom
    restamping: false
```

## License

This project is released under the Apache License 2.0. See the `LICENSE` file for details.

## Authors

This package was developed by **Jean Laneurit**.
