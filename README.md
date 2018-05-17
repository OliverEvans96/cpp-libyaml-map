# C++ Maps from YAML

- Uses [`libyaml`](http://pyyaml.org/wiki/LibYAML) instead of [`yaml-cpp`](https://github.com/jbeder/yaml-cpp) for the sake of C++98 compliance. I'm stuck with a compiler that doesn't support C++11.
- Creates a C++ [map](http://www.cplusplus.com/reference/map/map/) of vectors of strings out of the contents of the YAML file.
- Uses `libyaml`'s document-based parsing syntax.
- Does not support nested YAML mappings. This is intended only for very simple YAML files.
- Mapping keys are stored as vectors whether they are written as sequences or scalars in the YAML.
- Since all values are strings, they must be manually converted to the correct types.

e.g.

Input YAML (`yaml.config`)
```yaml
opt1: true
opt2: false
atoms: [4,3,5]
num: 3.5 
name: "myname"
```

Output map in C++
```yaml
atoms: ["4", "3", "5", ]
name: ["myname", ]
num: ["3.5", ]
opt1: ["true", ]
opt2: ["false", ]
```

You'll probably need to modify the Makefile to point to the PREFIX where `libyaml` is installed.

Based on advice from:
- https://stackoverflow.com/questions/36410122/c-libyaml-document-based-parsing
- http://staskobzar.blogspot.com/2017/04/yaml-documents-parsing-with-libyaml-in-c.html
- https://www.wpsoftware.net/andrew/pages/libyaml.html

