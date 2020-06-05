#include "pch.h"
#include "CppUnitTest.h"

#include "..\ImageConvertLib\IAction.h"
#include "..\ImageConvertLib\Actions.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ImageConvertUnitTest
{
	TEST_CLASS(ImageConvertUnitTest)
	{
	private:
		const std::string m_imagesPath = IMAGE_PATH;
	public:

		TEST_METHOD(CmdLoad)
		{
			std::string errorString;
			{
				const std::string imagePath = m_imagesPath + "examples.jpg";
				EActionResult result = Actions::run("  load  img \t" + imagePath + "  \t", &errorString);
				Assert::AreEqual(result == EActionResult::OK, true);
			}

			{
				const std::string imagePath = m_imagesPath + "mountains.jpg";
				EActionResult result = Actions::run("load  img1 \t" + imagePath, &errorString);
				Assert::AreEqual(result == EActionResult::OK, true);
			}

			{
				const std::string imagePath = m_imagesPath + "objects.jpg";
				EActionResult result = Actions::run("\t ld  img3 \t" + imagePath, &errorString);
				Assert::AreEqual(result == EActionResult::OK, true);
			}

			{
				EActionResult result = Actions::run("ld  img3 \tc:\\s:.jpg\t \t", &errorString);
				Assert::AreEqual(result == EActionResult::OK, false);
			}
		}

		TEST_METHOD(CmdStore)
		{
			std::string errorString;
			{
				const std::string imagePath = m_imagesPath + "examples.jpg";
				EActionResult result = Actions::run("  load  img \t" + imagePath + "  \t", &errorString);
				Assert::AreEqual(result == EActionResult::OK, true);
			}

			{
				const std::string imagePath = m_imagesPath + "tmp\\1.jpg";
				EActionResult result = Actions::run("  store  img \t" + imagePath + "  \t", &errorString);
				Assert::AreEqual(result == EActionResult::OK, true);
				//@todo Assert check exist file
			}

			{
				const std::string imagePath = m_imagesPath + "tmp\\3.jpg";

				EActionResult result = Actions::run("store  img \t" + imagePath, &errorString);
				Assert::AreEqual(result == EActionResult::OK, true);
				//@todo Assert check exist file
			}

			{
				const std::string imagePath = m_imagesPath + "tmp\\4.jpg";

				EActionResult result = Actions::run("\t s  img1 \t" + imagePath, &errorString);
				Assert::AreEqual(result == EActionResult::OK, false);
				//@todo Assert check exist file
			}

			{
				EActionResult result = Actions::run("s  img \tc:\\s:.jpg\t \t", &errorString);
				Assert::AreEqual(result == EActionResult::OK, false);
				//@todo Assert check exist file
			}

		}

		TEST_METHOD(CmdBlur)
		{
			std::string errorString;

			{
				const std::string imagePath = m_imagesPath + "examples.jpg";
				EActionResult result = Actions::run("  load  img \t" + imagePath + "  \t", &errorString);
				Assert::AreEqual(result == EActionResult::OK, true);
			}

			{
				EActionResult result = Actions::run("  blur  img \timg1  \t 7 \t", &errorString);
				Assert::AreEqual(result == EActionResult::OK, true);
			}

			{
				EActionResult result = Actions::run("blur  img1 \timg2  \t 5 \t", &errorString);
				Assert::AreEqual(result == EActionResult::OK, true);
			}

			{
				EActionResult result = Actions::run("blur  img1 \timg2  \t 10 \t", &errorString);
				Assert::AreEqual(result == EActionResult::OK, true);
			}

			{
				EActionResult result = Actions::run("blur  img1 \timg3  \t dsf \t", &errorString);
				Assert::AreEqual(result == EActionResult::OK, false);
			}

		}

		TEST_METHOD(CmdResize)
		{
			std::string errorString;

			{
				const std::string imagePath = m_imagesPath + "examples.jpg";
				EActionResult result = Actions::run("  load  img \t" + imagePath + "  \t", &errorString);
				Assert::AreEqual(result == EActionResult::OK, true);
			}

			{
				EActionResult result = Actions::run("  resize  img \timg1  \t 1024 \t 2048   ", &errorString);
				Assert::AreEqual(result == EActionResult::OK, true);
			}

			{
				EActionResult result = Actions::run("resize  img1 \timg2  \t 2048 \t4096\t", &errorString);
				Assert::AreEqual(result == EActionResult::OK, true);
			}

			{
				EActionResult result = Actions::run("resize  img1 \timg2  \t 4096 \t 8192", &errorString);
				Assert::AreEqual(result == EActionResult::OK, true);
			}

			{
				EActionResult result = Actions::run("resize  img1 \timg3 123 \t dsf \t", &errorString);
				Assert::AreEqual(result == EActionResult::OK, false);
			}

		}

		TEST_METHOD(CmdExit)
		{
			std::string errorString;

			{
				EActionResult result = Actions::run("  exit \t", &errorString);
				Assert::AreEqual(result == EActionResult::NEEDTERMINATE, true);
			}

			{
				EActionResult result = Actions::run("quit \t", &errorString);
				Assert::AreEqual(result == EActionResult::NEEDTERMINATE, true);
			}

			{
				EActionResult result = Actions::run("q \t", &errorString);
				Assert::AreEqual(result == EActionResult::NEEDTERMINATE, true);
			}

		}

		TEST_METHOD(CmdHelp)
		{
			std::string errorString;

			{
				EActionResult result = Actions::run("  help\t", &errorString);
				Assert::AreEqual(result == EActionResult::HELP, true);
			}

			{
				EActionResult result = Actions::run("h \t", &errorString);
				Assert::AreEqual(result == EActionResult::HELP, true);
			}
		}

	};

}
