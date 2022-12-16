//
// Created by ghuno on 2022-03-21.
//

#ifndef TESTER_USEFUL_MACROS_H
#define TESTER_USEFUL_MACROS_H

#define THROUGH_CONTAINER(container_type, container_name, IT) ( container_type::iterator IT=container_name.begin(); IT!=container_name.end(); IT++)
#define THROUGH_CONTAINER(container_type, container_name) ( container_type::iterator IT=container_name.begin(); IT!=container_name.end(); IT++)
#define IRANGE(num, i) (int i=0;i<num;i++)
#define IRANGE(num) (int i=0;i<num;i++)
#define URANGE(num, i) (unsigned int i=0;i<num;i++)
#define URANGE(num) (unsigned int i=0;i<num;i++)

#endif //TESTER_USEFUL_MACROS_H
