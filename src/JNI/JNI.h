#pragma once

#include <memory>
#include <jni.h>
#include <Windows.h>

#include "./classes/CRobot.h"

class JNI final 
{
	public:
		JNI() {
			/* init main pointers */
			{
				jint result = JNI_GetCreatedJavaVMs(&p_jvm, 1, nullptr);

				if (result != 0) {
					printf("[-] JNI() failed to initialize p_jvm\n");
					MessageBoxA(0, "ERROR", "Check console", MB_ICONASTERISK);
				}

				p_jvm->AttachCurrentThread((void**)&p_env, nullptr);
			}
            
            /* init game classes */
            {
                p_crobot = std::make_unique<CRobot>(p_env);
            }

            is_init = true;
		}

        ~JNI()
        {
            p_jvm->DetachCurrentThread();

            is_init = false;
        }

        bool GetInit()
        {
            return is_init;
        }
        
        std::unique_ptr<CRobot> p_crobot;
	private:
		JavaVM* p_jvm;
		JNIEnv* p_env;

        bool is_init{ false };
};

inline std::unique_ptr<JNI> p_jni;
