
import numpy as np
import matplotlib.pyplot as plt

# ============================================================
# USER INPUT
# ============================================================

m1 = 1.0e26
m2 = 1.0e26

filename = "output/trajectory.csv"

# ============================================================
# LOAD CSV FILE
# ============================================================

print("Loading trajectory data...")

data = np.loadtxt(filename, delimiter=",")

# ============================================================
# EXTRACT DATA
# ============================================================

t = data[:, 0]

X1 = data[:, 1]
Y1 = data[:, 2]
Z1 = data[:, 3]

X2 = data[:, 4]
Y2 = data[:, 5]
Z2 = data[:, 6]

VX1 = data[:, 7]
VY1 = data[:, 8]
VZ1 = data[:, 9]

VX2 = data[:, 10]
VY2 = data[:, 11]
VZ2 = data[:, 12]

# ============================================================
# CENTER OF MASS
# ============================================================

XG = (m1 * X1 + m2 * X2) / (m1 + m2)
YG = (m1 * Y1 + m2 * Y2) / (m1 + m2)
ZG = (m1 * Z1 + m2 * Z2) / (m1 + m2)

# ============================================================
# COMMON AXIS SETTINGS
# ============================================================

def common_axis_settings(ax):

    ax.set_box_aspect([1, 1, 1])

    ax.set_xlabel("X (km)")
    ax.set_ylabel("Y (km)")
    ax.set_zlabel("Z (km)")

    ax.grid(True)

    ax.view_init(elev=30, azim=45)

# ============================================================
# FIGURE 1
# ============================================================

fig1 = plt.figure(figsize=(10, 8))

ax1 = fig1.add_subplot(111, projection='3d')

ax1.plot(X1, Y1, Z1, label='Body 1')
ax1.plot(X2, Y2, Z2, label='Body 2')
ax1.plot(XG, YG, ZG, label='Center of Mass')

ax1.set_title(
    'Figure 2.3: Motion relative to the inertial frame'
)

ax1.legend()

common_axis_settings(ax1)

# ============================================================
# FIGURE 2
# ============================================================

fig2 = plt.figure(figsize=(10, 8))

ax2 = fig2.add_subplot(111, projection='3d')

ax2.plot(
    X2 - X1,
    Y2 - Y1,
    Z2 - Z1,
    label='m2 relative to m1'
)

ax2.plot(
    XG - X1,
    YG - Y1,
    ZG - Z1,
    label='G relative to m1'
)

ax2.set_title(
    'Figure 2.4a: Motion of m2 and G relative to m1'
)

ax2.legend()

common_axis_settings(ax2)

# ============================================================
# FIGURE 3
# ============================================================

fig3 = plt.figure(figsize=(10, 8))

ax3 = fig3.add_subplot(111, projection='3d')

ax3.plot(
    X1 - XG,
    Y1 - YG,
    Z1 - ZG,
    label='m1 relative to G'
)

ax3.plot(
    X2 - XG,
    Y2 - YG,
    Z2 - ZG,
    label='m2 relative to G'
)

ax3.set_title(
    'Figure 2.4b: Motion of m1 and m2 relative to G'
)

ax3.legend()

common_axis_settings(ax3)

plt.show()
