
release_env = Environment(CCFLAGS = ['-O2','-DRENDER_INFO','-std=c++11'])
#debug_env = release_env.Clone(CCFLAGS = ['-g'])
#debug_env = release_env.Clone(CCFLAGS = ['-g','-pg'],LINKFLAGS=['-g','-pg'])
debug_env = release_env.Clone()


debug_env.Replace(CXXCOMSTR = "Compiling $TARGET")
debug_env.Replace(SHCXXCOMSTR = "Compiling $TARGET")
debug_env.Replace(CCCOMSTR = "Compiling $TARGET")
debug_env.Replace(SHCCCOMSTR = "Compiling $TARGET")
debug_env.Replace(LINKCOMSTR = "Linking $TARGET")
debug_env.Replace(SHLINKCOMSTR = "Linking $TARGET")

#SConscript('src/SConscript', variant_dir='release', exports={'env':release_env})
SConscript('src/SConscript', variant_dir='debug', exports={'env':debug_env})

