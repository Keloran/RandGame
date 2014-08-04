#include "./Singleton.hpp"
#include "../ExceptionHandler/ExceptionHandler.hpp"

namespace NordicArts {
	struct SingletonInfo {
		const std::string	cSingletonName;
		bool 				bIsConstructed;

		SingletonInfo(const std::string &cName) : cSingletonName(cName), bIsConstructed(false) {}
	};

	static std::array<SingletonInfo, 4> s_aSingletons = {
		SingletonInfo("Logger"),
		SingletonInfo("Settings"),
		SingletonInfo("Engine"),
		SingletonInfo("ShaderManager")
	};

	Singleton::Singleton(SingletonType eType) : m_eType(eType) {
		bool bSaveInLog = s_aSingletons.at(TYPE_LOGGER).bIsConstructed;

		try {
			if (!s_aSingletons.at(eType).bIsConstructed) {
				for (int i = 0; i < eType; ++i) {
					if (!s_aSingletons.at(i).bIsConstructed) {
						throw ExceptionHandler(s_aSingletons.at(i).cSingletonName + " must be constructed by extension", bSaveInLog);
					}
				}

				s_aSingletons.at(eType).bIsConstructed = true;
			} else {
				throw ExceptionHandler(s_aSingletons.at(eType).cSingletonName + " can only be constructed once", bSaveInLog);
			}
		} catch (std::exception &) {
			std::ostringstream cStream;
			cStream << __FUNCTION__ << " Invalid Singleton Type " << eType;

			throw ExceptionHandler(cStream, bSaveInLog);
		}
	}

	Singleton::~Singleton() {
		s_aSingletons.at(m_eType).bIsConstructed = false;
	}
};