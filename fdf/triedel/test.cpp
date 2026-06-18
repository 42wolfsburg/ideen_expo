#include <gtest/gtest.h>

extern "C" {
	#include "all.h"
	#include "display.h"
};

TEST(model, normalize)
{
	t_color c = clt(0, 0, 0, 100);
	EXPECT_EQ(cl_opac(c), 155);
}

TEST(color, basic)
{
	t_color c = clt(1, 2, 3, 4);
	EXPECT_EQ(cl_red(c), 1);
	EXPECT_EQ(cl_green(c), 2);
	EXPECT_EQ(cl_blue(c), 3);
	EXPECT_EQ(cl_trans(c), 4);
	EXPECT_EQ(cl_opac(c), 251);
}

TEST(color, add)
{
	t_color c1 = cl(100, 0, 200);
	t_color c2 = cl(0, 100, 200);

	t_color res = cl_add(c1, c2);
	EXPECT_EQ(cl_red(res), 100);
	EXPECT_EQ(cl_green(res), 100);
	EXPECT_EQ(cl_blue(res), 255);
}

TEST(fdf, load)
{
	t_fdf *f = fdf_load(open("maps/42.fdf", O_RDONLY));
	EXPECT_NE(f, (t_fdf *) NULL);
	EXPECT_NE(*f, (t_fdf) NULL);
	// fdf_print(f);
}

TEST(model, load)
{
	t_model *m = model_load("maps/42.fdf");
	EXPECT_NE(m, (t_model *) NULL);
}

int	main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return (RUN_ALL_TESTS());
}
