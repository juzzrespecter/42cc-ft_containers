/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 18:34:02 by danrodri          #+#    #+#             */
/*   Updated: 2021/10/21 17:50:11 by danrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Help remove template resolutions
 * B == true; enable_if has a public member typedef
 */

#ifndef __ENABLE_IF__
#define __ENABLE_IF__

namespace  ft {

template< bool B, class T = void >
	struct enable_if { };

template< class T >
	struct enable_if< true, T > { typedef T type; };

}

#endif
