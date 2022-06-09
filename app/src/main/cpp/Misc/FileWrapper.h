//
// Created by letha on 9/9/2021.
//

#ifndef IMGUIANDROID_FILEWRAPPER_H
#define IMGUIANDROID_FILEWRAPPER_H
class File
{
public:
    File(std::string path)
    {
        auto env = getEnv();
        auto context_class = env->FindClass("android/content/Context");
        auto file_class = env->FindClass("java/io/File");
        auto get_files_dir_method = env->GetMethodID(context_class, "getFilesDir", "()Ljava/io/File;");
        auto file_get_path = env->GetMethodID(file_class, "getAbsolutePath", "()Ljava/lang/String;");
        auto file_object = env->CallObjectMethod(getGlobalContext(env), get_files_dir_method);
        auto jpath = (jstring) env->CallObjectMethod(file_object, file_get_path);
        auto base_path = std::string(env->GetStringUTFChars(jpath, 0));

        this->path = base_path + "/" + path;
        env->ReleaseStringUTFChars(jpath, base_path.c_str());
    }
    bool file_exists()
    {
        if (access(path.c_str(), F_OK) == -1)
            return false;

        return true;
    }
    std::string read_content()
    {
        const std::ifstream input_stream(path, std::ios_base::binary);

        if (input_stream.fail()) {
            throw std::runtime_error("Failed to open file");
        }

        std::stringstream buffer;
        buffer << input_stream.rdbuf();

        return buffer.str();
    }
    std::ifstream get_stream()
    {
        return std::ifstream(path);
    }
    void write_text(std::string content)
    {

        std::ofstream fs(path.c_str());
        if (!fs.is_open()) {
            LOGW("open, Error opening file %s", path.c_str());
            fs.open(path.c_str(), std::ios::out);
        }
        fs << content;
        LOGD("FILE WROTE");
    }
    int write_text(const char* content, bool force = false)
    {
        FILE* file = fopen(path.c_str(),force ? "w+" : "wx");
        int wrote;
        if (file != NULL)
        {
            fputs(content, file);
            wrote = fflush(file);

            LOGD("Bytes Written->%i", wrote);
            fclose(file);
        }
        return wrote;
    }
private:
    std::string path;
};
#endif //IMGUIANDROID_FILEWRAPPER_H
