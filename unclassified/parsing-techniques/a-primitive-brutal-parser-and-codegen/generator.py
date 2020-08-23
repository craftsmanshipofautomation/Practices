from rwparser import JavaParser, RWParser0
import re
import shutil
import os


class HandlerA(object):
    @staticmethod
    def jsonDump(src_file):
        _parser = RWParser0()
        prejson = _parser.parse(src_file)
        for item in prejson:
            print item

    @staticmethod
    def rip(src, rm):
        return src.replace(rm, "")

    @staticmethod
    def is_picture(word):
        return word.endswith(".png")

    @staticmethod
    def is_number(word):
        if word.isdigit():
            return True
        pat = re.compile(r"\d+\.\d+[f]{0,1}")
        m = pat.match(word)
        if m:
            return True
        return False

    @staticmethod
    def is_anonymous_obj(word):
        if word.startswith("new"):
            return True

    @staticmethod
    def dealWithData(_tuple):
        pass


class Generator(object):
    @staticmethod
    def qoute(line):
        return '"' + line + '"'

    def __init__(self):
        self.__init0__()

    def __init0__(self):
        p = JavaParser()
        p.read("./source_code.data")
        self.keys = p.parse()
        p = RWParser0()
        self.ref = p.parse("./source_code.data")
        ###fuck !!!!!!!!!
        size = len(self.keys)
        for i in xrange(size):
            if self.keys[i][0] == "NoneFilterRender":
                new = ("FilterRender", self.keys[i][1])
                self.keys.pop(i)
                self.keys.append(new)
                print ("Changing NoneFilterRender to FilterRender")
                break
        for k in self.ref:
            if k == "NoneFilterRender":
                v = self.ref[k]
                self.ref.pop(k, None)
                self.ref["FilterRender"] = v
                print ("Changing NoneFilterRender to FilterRender")

    def make_instructions(self):
        '''
        demo:
        ::json_object* jo = ::json_object_new_object();
        FOO::json_set_int(jo, "type", type);
        FOO::json_set_string(jo, "tex3path", "/data/local/tmp/lomo_map.png");
        '''
        instruction_dictionary = {}
        lm1 = 'std::string attr_str = "";'
        l0 = "::json_object* _json = ::json_object_new_object();"
        lend0 = 'attr_str = ::json_object_to_json_string(_json);'
        lend1 = '::json_object_put(_json);'
        lend2 = "return attr_str;"
        for tup in self.keys:
            lines = []
            lines.append(lm1) #append
            lines.append(l0)  #append
            renderer = tup[0]
            keys = tup[1]
            args = self.ref[renderer]
            # type
            l1 = 'FOO::json_set_int(_json, "type", {type_str});'.format(type_str="FOO::k"+renderer)
            lines.append(l1) #append
            size = len(args)
            if size:
                for i in xrange(0, size):
                    key = keys[i][0]
                    value = args[i]
                    if keys[i][1] == "String":
                        ln = 'FOO::json_set_string(_json, "{key}", {value});'.format(key=key, value=value)
                        lines.append(ln) #append
                        continue
                    if keys[i][1] == "Float":
                        ln = 'FOO::json_set_double(_json, "{key}", {value});'.format(key=key, value=value)
                        lines.append(ln) #append
                        continue
                    if keys[i][1] == "PointF":
                        # value : newPointF(0.5f,0.5f) -> 0.5f, 0.5f
                        # FOO::json_set_point(jo, "center", 0.5f, 0.5f);
                        value = value.replace("newPointF", "").replace("(", "").replace(")", "")
                        ln = 'FOO::json_set_point(_json, "{key}", {value});'.format(key=key, value=value)
                        lines.append(ln) #append
                        continue
                    if keys[i][1] == "Color4F":
                        # value = newColor4F(1.0f,0.0f,1.0f,1.0f)-> 1.0f, 0.0f, 1.0f, 1.0f
                        # FOO::json_set_color(jo, "color", 1.0f, 0.0f, 1.0f, 1.0f);
                        value = value.replace("newColor4F", "").replace("(", "").replace(")", "")
                        ln = 'FOO::json_set_color(_json, "{key}", {value});'.format(key=key, value=value)
                        lines.append(ln) #append
                        continue
                    if keys[i][1] == "FloatArray":
                        #newfloat[]{0.3f,0.0f,1.0f} -> {0.3f,0.0f,1.0f}
                        value = value.replace("newfloat[]", "")
                        length = value.count(",") + 1
                        ln0 = 'float {key}[{length}] = {value};'.format(key=key, length=length, value=value)
                        ln1 = 'FOO::json_set_float_array(_json, "{key}", {key}, {length});'.format(key=key, length=length)
                        lines.append(ln0) #append
                        lines.append(ln1) #append
                        continue
                else:
                    pass
            lines.append(lend0) #append
            lines.append(lend1) #append
            lines.append(lend2) #append
            instruction_dictionary[renderer] = lines
        #end for
        return instruction_dictionary

    @staticmethod
    def fill_template_variable(line, _dict = {}):
        size = len(line)
        variables = []
        i = 0
        while True:
            if line[i] == "{" and line[i+1] == "{":
                j = i+2
                while True:
                    if line[i] == "}" and line[i+1] == "}":
                        break
                    i += 1
                var = line[j:i]
                var = var.strip()
                sub = _dict[var]
                variables.append((line[j-2:i+2], sub))
            if i >= size-1:
                break
            i += 1
        # fill
        for part, sub in variables:
            line = line.replace(part, sub)
        return line

    def __generate__(self, template, output, _dict={}):
        with open(template, "r") as rf, open(output, "w") as wf:
            for line in rf:
                line = Generator.fill_template_variable(line, _dict)
                wf.write(line)
    
    def generate(self):
        dictionary = self.make_instructions()
        for renderer_name in dictionary:
            test_name = self.test_prefix + renderer_name
            test_file = self.output_abs_dir + test_name + self.test_file_postfix
            _dict = {}
            _dict["TEST_NAME"] = test_name
            _dict["TEST_PICTURE"] = self.testee_image_abs
            _dict["TEST_IMAGE_OUTPUT"] = Generator.qoute(self.test_result_abs_dir + renderer_name + self.test_output_image_postfix)
            _dict["TEST_JSONGEN"] = "".join(["\t" + line + "\n" for line in dictionary[renderer_name]])
            print ("Creating file {}".format(test_file))
            self.__generate__(self.template, test_file, _dict)

    def setup_env(self, output_dir):
        # todo: use a config file
        self.output_abs_dir = output_dir + "/" if not output_dir.endswith("/") else output_dir
        self.src_image_relative_dir = "data/filters/"
        self.testee_image_relative = Generator.qoute("data/testee/1.png")
        self.test_prefix =  "Test_"
        self.test_file_postfix = ".cpp"
        self.test_output_image_postfix = ".jpg"
        self.test_result_relative_dir = "out/"
        self.template = "template.cpp"
        # fuck android
        self.remote_test_dir = "/data/local/tmp/filter_test/"
        self.testee_image_abs = Generator.qoute(self.remote_test_dir + "data/testee/1.png")
        self.test_result_abs_dir = self.remote_test_dir + self.test_result_relative_dir
        self.src_image_abs_dir = self.remote_test_dir + self.src_image_relative_dir
        # remove all fuck
        # use relative path
        if os.path.exists(self.output_abs_dir):
            shutil.rmtree(self.output_abs_dir)
        # create and copy
        shutil.copytree("data/", self.output_abs_dir+"data/")
        shutil.copytree("include/", self.output_abs_dir+"include/")

        self.localize()
        self.create_cmake()
        self.create_make()

    def localize(self):
        # 1, adjust resource path
        for key in self.ref:
            new_args = []
            for i in self.ref[key]:
                if i.endswith(".png"):
                    pathized = Generator.qoute(self.src_image_abs_dir + i)
                    new_args.append(pathized)
                else:
                    new_args.append(i)
            self.ref[key] = new_args

    def create_cmake(self):
        project_cmd0 = "project(glcore_filter_test)\n"
        copy_cmd0 = "file(COPY data DESTINATION ${PROJECT_BINARY_DIR})\n"
        copy_cmd1 = "file(COPY RunTestMakefile DESTINATION ${PROJECT_BINARY_DIR})\n"
        mkdir_cmd0 = "file(MAKE_DIRECTORY ${{PROJECT_BINARY_DIR}}/{})\n".format(self.test_result_relative_dir.replace("/", ""))
        with open(self.output_abs_dir+"CMakeLists.txt", "w") as cmake:
            cmake.write(project_cmd0)
            cmake.write(copy_cmd0)
            cmake.write(copy_cmd1)
            cmake.write(mkdir_cmd0)
            for renderer in self.ref:
                add_exectable = "add_executable({renderer} {test_file})\n".format(renderer=renderer,
                    test_file=self.test_prefix + renderer + self.test_file_postfix)
                cmake.write(add_exectable)
            for renderer in self.ref:
                link_cmd1 = """TARGET_LINK_LIBRARIES({renderer} test_utils)\n""".format(
                                                renderer = renderer)
                cmake.write(link_cmd1)

    def create_make(self):
        cmd0 = "DST_DIR := /data/local/tmp/filter_test\n"
        cmd_all_pat = "all: {list_}\n"
        lst = ""
        n = 0
        for r in self.ref:
            lst += "Test_" + r
            lst += " "
            n += 1
            if (n == 3):
                lst += "\\\n\t\t"
                n = 0
        lst += "# end all"
        cmd_all = cmd_all_pat.format(list_=lst)
        cmd01 = "prepare:\n"
        cmd02 = "\tadb shell mkdir -p $(DST_DIR)\n"
        cmd03 = "\tadb shell mkdir $(DST_DIR)/out\n"
        cmd04 = "\tadb push data $(DST_DIR)\n"
        cmd10 = "Test_{renderer_exe}: {result_dir}{renderer}{postfix}\n"
        cmd1 = "{result_dir}{renderer}{postfix}:\n"
        cmd2 = "\tadb push {renderer_exe} $(DST_DIR)\n"
        cmd3 = "\tadb shell chmod 755 $(DST_DIR)/{renderer_exe}\n"
        cmd4 = "\tadb shell $(DST_DIR)/{renderer_exe}\n"
        cmd5 = "\tadb pull $(DST_DIR)/{result_dir}{renderer_exe}{postfix} {result_dir}{renderer_exe}{postfix}\n"
        with open(self.output_abs_dir+"RunTestMakefile", "w") as make:
            make.write(cmd0)
            make.write("\n")
            make.write(cmd_all)
            make.write("\n")
            make.write(cmd01)
            make.write(cmd02)
            make.write(cmd03)
            make.write(cmd04)
            make.write("\n")
            for exe in self.ref:
                make.write(cmd10.format(renderer_exe=exe, result_dir=self.test_result_relative_dir,
                                renderer=exe, postfix=self.test_output_image_postfix))
                make.write(cmd1.format(result_dir=self.test_result_relative_dir,
                                renderer=exe, postfix=self.test_output_image_postfix))
                make.write(cmd2.format(renderer_exe=exe))
                make.write(cmd3.format(renderer_exe=exe))
                make.write(cmd4.format(renderer_exe=exe))
                make.write(cmd5.format(renderer_exe=exe, postfix=self.test_output_image_postfix,
                                result_dir=self.test_result_relative_dir))
                make.write("\n")


if __name__ == "__main__":
    g = Generator()
    output_dir="/home/root_/test/filter_test"
    g.setup_env(output_dir)
    g.generate()
