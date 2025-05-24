#ifndef SSEU_HPP
#define SSEU_HPP

#include "sseu_headers.hpp"
#include <iostream>

namespace Sseu {
	// const double inf{*reinterpret_cast<double *>(const_cast<wchar_t *>(L"\u0000\u0000\u0000\u7ff0"))};

	::SDL_Window *window;
	::SDL_Renderer *renderer;
	::SDL_GLContext gl_context;
	::int32_t wnd_x, wnd_y, wnd_width, wnd_height;
	::int32_t vp_x, vp_y, vp_width, vp_height;
	bool running{true};

	struct ActivityBase{
		virtual ~ActivityBase() = default;
		virtual void init() = 0;
		virtual void quit() = 0;
		virtual void update() = 0;
		virtual void procedure(::SDL_Event const) = 0;
	};

	struct ActivityStack{
		struct Node{
			::Sseu::ActivityBase *activity;
			::Sseu::ActivityStack::Node *prev;
		};
		Node *base;
		Node *should_push;
		bool should_pop;
		inline ActivityStack(): base{nullptr}, should_push{nullptr}, should_pop{false} { }
		inline void push() {
			if (this->base != nullptr) {
				this->base->activity->quit();
			}
			// (this->base = new ::Sseu::ActivityStack::Node{new T, this->base})->activity->init();
// ::std::cout<<"__LINE__: "<<__LINE__<<"\tbase\t"<<this->base<<'\n';
			(this->base = this->should_push)->activity->init();
// ::std::cout<<"__LINE__: "<<__LINE__<<"\tbase\t"<<this->base<<'\n';
																// ::std::cout<<"__LINE__: "<<__LINE__<<"\tbase\t"<<this->base<<'\n';
																// ::std::cout<<"__LINE__: "<<__LINE__<<"\tactivity\t"<<this->base->activity<<'\n';
		}
		inline void pop() {
			::Sseu::ActivityStack::Node *deleted_node{this->base};
			this->base = this->base->prev;
			deleted_node->activity->quit();
																// ::std::cout<<"__LINE__: "<<__LINE__<<"\tactivity\t"<<deleted_node->activity<<'\n';
			delete deleted_node->activity;
																// ::std::cout<<"__LINE__: "<<__LINE__<<"\tnode\t"<<deleted_node<<'\n';
			// delete deleted_node;
																// ::std::cout<<"__LINE__: "<<__LINE__<<"\tbase\t"<<this->base<<'\n';
			if (this->base != nullptr) {
				this->base->activity->init();
			}
																// ::std::cout<<"__LINE__: "<<__LINE__<<'\t'<<this->base<<'\n';
																// ::std::cout<<"__LINE__: "<<__LINE__<<'\t'<<"Main activity popped.\n";
		}
		template<typename T> inline T *top() const {
			return static_cast<T *>(this->base->activity);
		}
		inline bool empty() const {
			return this->base == nullptr;
		}
	} activity_stack;

	// template<typename T> void push_activity() {
	//     activity_stack.push(new T);
	//     activity_stack.top()->init();
	// }
	// void pop_activity() {
	//     delete activity_stack.top();
	//     activity_stack.pop();
	//     if (!activity_stack.empty()) {
	//                                                             // std::cout<<__LINE__<<'\n';
	//         activity_stack.top()->init();
	//                                                             // std::cout<<__LINE__<<'\n';
	//     }
	// }

	inline void set_base_projection() {
		const double half_width{::Sseu::vp_width * 0.5};
		const double half_height{::Sseu::vp_height * 0.5};
		::glMatrixMode(GL_PROJECTION);
		::glLoadIdentity();
		// ::glOrtho(0.0, ::Sseu::vp_width, 0.0, ::Sseu::vp_height, 0.0, INT_MAX);
		::glFrustum(-half_width, half_width, -half_height, half_height, 1.0, 2.0);
	}
	inline void set_base_modelview() {
		const double eye_x{::Sseu::vp_width * 0.5};
		const double eye_y{::Sseu::vp_height * 0.5};
		::glMatrixMode(GL_MODELVIEW);
		::glLoadIdentity();
		// ::gluLookAt(0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		::gluLookAt(eye_x, eye_y, 1.0, eye_x, eye_y, 0.0, 0.0, 1.0, 0.0);
		// ::gluLookAt(eye_x, eye_y, 1.0, eye_x, eye_y, 0.0, 0.0, 1.0, 0.0);
	}
	inline void set_viewport(::int32_t x, ::int32_t y, ::int32_t width, ::int32_t height) {
		// double eye_x{width * 0.5};
		// double eye_y{height * 0.5};
		::Sseu::vp_x = x;
		::Sseu::vp_y = y;
		::Sseu::vp_width = width;
		::Sseu::vp_height = height;
		::glViewport(x, y, width, height);
		// ::glMatrixMode(GL_PROJECTION);
		// ::glLoadIdentity();
		// ::glOrtho(0.0, width, 0.0, height, 0.0, INT_MAX);
		// ::glScissor(x, y, width, height);
		// ::Sseu::set_base_projection();
		// ::glMatrixMode(GL_MODELVIEW);
		// ::glLoadIdentity();
		// ::gluLookAt(0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		// ::gluLookAt(eye_x, eye_y, 1.0, eye_x, eye_y, 0.0, 0.0, 1.0, 0.0);
	}

	inline void init(char const *title, ::int32_t x, ::int32_t y, ::int32_t width, ::int32_t height) {
		::SDL_Init(SDL_INIT_VIDEO);
		::SDL_Init(SDL_INIT_AUDIO);
		::Sseu::window = ::SDL_CreateWindow(title, x, y, width, height, ::SDL_WindowFlags::SDL_WINDOW_OPENGL);
		::Sseu::renderer = ::SDL_CreateRenderer(window, -1, 0U);
		::Sseu::gl_context = ::SDL_GL_CreateContext(window);
		::Sseu::wnd_x = x;
		::Sseu::wnd_y = y;
		::Sseu::wnd_width = width;
		::Sseu::wnd_height = height;
	}

	inline void quit() {
		::SDL_GL_DeleteContext(::Sseu::gl_context);
																// ::std::cout<<"__LINE__: "<<__LINE__<<'\t'<<'\n';
		::SDL_DestroyRenderer(::Sseu::renderer);
																// ::std::cout<<"__LINE__: "<<__LINE__<<'\t'<<'\n';
		::SDL_DestroyWindow(::Sseu::window);
																// ::std::cout<<"__LINE__: "<<__LINE__<<'\t'<<'\n';
		::SDL_Quit();
																// ::std::cout<<"__LINE__: "<<__LINE__<<'\t'<<'\n';
	}

	template<typename T> inline void push_activity() {
		// ::Sseu::activity_stack.push<T>();
		::Sseu::activity_stack.should_push = new ::Sseu::ActivityStack::Node{new T, ::Sseu::activity_stack.base};
	}

	inline void pop_activity() {
		::Sseu::activity_stack.should_pop = true;
	}

	template<typename T> inline T *top_activity() {
		return ::Sseu::activity_stack.top<T>();
	}

	inline void mainloop() {
		::SDL_Event event;
																// try{
		while (::Sseu::running) {
			if (::Sseu::activity_stack.should_push != nullptr) {
// ::std::cout<<"__LINE__: "<<__LINE__<<'\n';
				::Sseu::activity_stack.push();
				::Sseu::activity_stack.should_push = nullptr;
// ::std::cout<<"__LINE__: "<<__LINE__<<'\n';
			}
			// ::Sseu::activity_stack.lock();
			while (::SDL_PollEvent(&event)) {
				if (event.type == ::SDL_EventType::SDL_QUIT) {
					::Sseu::running = false;
				} else {
					::Sseu::activity_stack.top<::Sseu::ActivityBase>()->procedure(event);
				}
			}
																// ::std::cout<<__LINE__<<'\n';
			::Sseu::activity_stack.top<::Sseu::ActivityBase>()->update();
			// ::Sseu::activity_stack.unlock();
			if (::Sseu::activity_stack.should_pop) {
				::Sseu::activity_stack.should_pop = false;
// ::std::cout << "__LINE__" << __LINE__ << '\n';
				::Sseu::activity_stack.pop();
// ::std::cout << "__LINE__" << __LINE__ << '\n';
			}
			if (::Sseu::activity_stack.empty()) {
																// ::std::cout<<"__LINE__: "<<__LINE__<<'\t'<<"Activity stack is empty.\n";
				break;
			}
																// ::std::cout<<__LINE__<<'\n';
		}
// }catch(::std::exception const &e){::std::cout<<"here:"<<'\n'<<e.what()<<'\n';}
																// }catch(const ::std::exception&e){
																//  ::std::cout<<"Error: ";
																//  ::std::cout<<e.what()<<'\n';
																// }
	}
}

#endif
