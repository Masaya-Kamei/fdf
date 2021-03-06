# 42 fdf

Draw a simplified 3D graphic representation of a relief landscape with parallel projection.

## Usage

`./fdf [map_file]`

Map example:

```txt
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0 10 10  0  0 10 10  0  0  0 10 10 10 10 10  0  0  0
0  0 10 10  0  0 10 10  0  0  0  0  0  0  0 10 10  0  0
0  0 10 10  0  0 10 10  0  0  0  0  0  0  0 10 10  0  0
0  0 10 10 10 10 10 10  0  0  0  0 10 10 10 10  0  0  0
0  0  0 10 10 10 10 10  0  0  0 10 10  0  0  0  0  0  0
0  0  0  0  0  0 10 10  0  0  0 10 10  0  0  0  0  0  0
0  0  0  0  0  0 10 10  0  0  0 10 10 10 10 10 10  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
```

## Demo

![fdf](https://user-images.githubusercontent.com/50983708/153358359-3cae0d77-476d-481e-b254-cf85210f0178.gif)

## Script

```zsh
git clone https://github.com/Masaya-Kamei/fdf.git --recursive;
cd fdf;
make;
./fdf maps/42.fdf;
```

- Rotate: Arrow key  
- Zoom: Mouse wheel

## Tool

- [my libft](https://github.com/Masaya-Kamei/libft) (42 useful functions)
- [42 minilibx_macos](https://git.hexanyn.fr/42-bocal/minilibx/-/tree/master/minilibx_macos) (42 simple graphics library)
- [42 minilibx-linux](https://github.com/42Paris/minilibx-linux) (42 simple graphics library)
- [Github Actions](https://docs.github.com/ja/actions) (CI/CD tool)
