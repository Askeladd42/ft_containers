/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   All.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plam <plam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:55:43 by julpelle          #+#    #+#             */
/*   Updated: 2023/01/08 15:21:49 by plam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef ALL_HPP
# define ALL_HPP

///////////////////////
// Include Libraries //
///////////////////////

# include <iostream>
# include <string>
# include <cmath>
# include <limits>
# include <memory>
# include <fstream>
# include <cstddef>
# include <deque>
# include <vector>
# include <stack>
# include <map>

///////////////////////
//       Utils       //
///////////////////////

// Color
# include "../utils/colors.hpp"

///////////////////////
//     Containers    //
///////////////////////

# include "vector.hpp"
# include "stack.hpp"
# include "map.hpp"

///////////////////////
//     Iterators     //
///////////////////////

# include "../utils/iterator.hpp"

///////////////////////
//       Tests       //
///////////////////////

# include "../tests/basic/basicTest.hpp"
# include "../tests/basic/showContainer.hpp"
# include "../tests/preliminary/preliminary.hpp"
# include "../tests/vector/vectorTest.hpp"
# include "../tests/map/mapTest.hpp"
# include "../tests/compare/compare.hpp"
# include "../tests/preliminary/preliminary.hpp"

///////////////////////
//     Functions     //
///////////////////////

int 	error_msg(std::string msg, int color, int ret);
void 	print_header(std::string msg, std::string arg);





#endif