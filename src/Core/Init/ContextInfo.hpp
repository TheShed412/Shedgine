namespace Core{
 
  //OpenGL versions
  struct ContextInfo
  {
     int major_version, minor_version;
     bool core;
 
     ContextInfo()//default
     {
       major_version = 3;
       minor_version = 3;
       core = true;
     }
 
     ContextInfo(int major_version, int minor_version, bool core)
     {
       this->major_version = major_version;
       this->minor_version = minor_version;
       this->core = core;
     }

    ContextInfo(const ContextInfo& contextInfo)
    {
       core = contextInfo.core;
       major_version = contextInfo.major_version;
       minor_version = contextInfo.minor_version;
    }

    void operator=(const ContextInfo& contextInfo)
    {
       core = contextInfo.core;
       major_version = contextInfo.major_version;
       minor_version = contextInfo.minor_version;
    }
  };
}