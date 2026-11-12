#!/usr/bin/env python3
"""生成 compile_commands.json，供 clangd / Zed 使用（不依赖 bear 或 cmake）。"""
import argparse
import json
import os
import shlex


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--cc", default="gcc")
    ap.add_argument("--cxx", default="g++")
    ap.add_argument("--cflags", default="")
    ap.add_argument("--cxxflags", default="")
    ap.add_argument("sources", nargs="+")
    a = ap.parse_args()

    root = os.getcwd()
    obj_dir = os.path.join(root, "build", "obj")
    entries = []
    for src in a.sources:
        is_c = src.endswith(".c")
        driver = a.cc if is_c else a.cxx
        flags = shlex.split(a.cflags if is_c else a.cxxflags)
        abs_src = os.path.join(root, src)
        obj = os.path.join(obj_dir, os.path.splitext(os.path.basename(src))[0] + ".o")
        entries.append(
            {
                "directory": root,
                "file": abs_src,
                "output": obj,
                "arguments": [driver, *flags, "-c", abs_src, "-o", obj],
            }
        )

    out = os.path.join(root, "compile_commands.json")
    with open(out, "w", encoding="utf-8") as f:
        json.dump(entries, f, indent=2, ensure_ascii=False)
        f.write("\n")
    print(f"生成 {out}（{len(entries)} 个编译单元）")


if __name__ == "__main__":
    main()
