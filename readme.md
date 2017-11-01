# ofxJsonUtilsUtils

This addon contains utilities for [ofxJsonUtils](https://github.com/2bbb/ofxJsonUtils).  


## Features

### Live reload

Depends on [ofxWatchFile](https://github.com/nariakiiwatani/ofxWatchFile).  
See ofxWatchFile's readme for details.

### Handy implementation of loadJson/toJson

The more you use ofxJsonUtils, the more you write loadJson/toJson like this.  

```
	void loadJson(const ofJson &json) {
		ofxJsonUtils::load(json, kv(name), kv(age), kv(life), kv(score));
	}
	ofJson toJson() const {
		return ofxJsonUtils::create(kv(name), kv(age), kv(life), kv(score));
	}
```

Now you can do the same thing in one line.  

```
	JSON_FUNCS(name, age, life, score);
```

### Save/Load callbacks

You can set a listener to be called before saving or after loading.  
Typical case : You want to hold some features as indirect value(s) in json file. --> See example-callbacks.  

### ImGui binding

See example-imgui.

## License

The MIT License (MIT)

Copyright (c) 2017 nariakiiwatani

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
