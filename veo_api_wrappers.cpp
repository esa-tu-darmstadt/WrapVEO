# include "veo_api_wrappers.h"

#define xstr(s) str(s)
#define str(s) #s
#define PRINT_FILE_LINE __FILE__ \tline: __LINE__

#define sizeMB(x) x/1000000.0f

void wrapper_veo_api_version () {
  int version = veo_api_version ();
  std::cout << "\nAPI version of VE Offload: " << version << std::endl;
}

veo_proc_handle* wrapper_veo_proc_create (int venode) {
  veo_proc_handle* proc = veo_proc_create (venode);
  if (proc == NULL) {
    std::cout << "\tveo_proc_create():\tVE process creation failed: " << xstr(PRINT_FILE_LINE) << std::endl;
    std::exit(EXIT_FAILURE);
  }
  return proc;
}

void wrapper_veo_proc_destroy (veo_proc_handle* proc) {
  int status = veo_proc_destroy (proc);
  if (status == 0) {
    #ifdef PRINT_ALL_VEO_API
    std::cout << "\tveo_proc_destroy():\tVEO process handle is successfully destroyed." << std::endl;
    #endif
  }
  else if (status == -1) {
    std::cout << "\tveo_proc_destroy():\tVEO process handle destruction failed: " << xstr(PRINT_FILE_LINE) << std::endl;
    std::exit(EXIT_FAILURE);
  }
  else {
    std::cout << "\tveo_proc_destroy():\tnot expected!: " << xstr(PRINT_FILE_LINE) << std::endl;
    std::exit(EXIT_FAILURE);
  }
}

uint64_t wrapper_veo_load_library (veo_proc_handle* proc, const char* libname) {
  uint64_t library_handle = veo_load_library (proc, libname);
  if (library_handle == 0) {
    std::cout << "\tveo_load_library():\tlibrary loading request failed: " << xstr(PRINT_FILE_LINE) << std::endl;
    std::exit(EXIT_FAILURE);
  }
  return library_handle;
}

veo_thr_ctxt* wrapper_veo_context_open (veo_proc_handle* proc) {
  veo_thr_ctxt* ctxt = veo_context_open (proc);
  if (ctxt == NULL) {
    std::cout << "\tveo_context_open():\tfailed to create a VEO context: " << xstr(PRINT_FILE_LINE) << std::endl;
    std::exit (EXIT_FAILURE);
  }
  return ctxt;
}

void wrapper_veo_context_close (veo_thr_ctxt* ctx) {
  int status = veo_context_close (ctx);
  if (status == 0) {
    #ifdef PRINT_ALL_VEO_API
    std::cout << "\tveo_context_close():\tVEO context is successfully closed." << std::endl;
    #endif
  }
  else {
    std::cout << "\tveo_context_close():\tfailed to close VEO context: " << xstr(PRINT_FILE_LINE) << std::endl;
    std::exit (EXIT_FAILURE);
  }
}

uint64_t wrapper_veo_get_sym (veo_proc_handle* proc, uint64_t libhdl, const char* symname) {
  uint64_t symbol = veo_get_sym (proc, libhdl, symname);
  if (symbol == 0) {
    std::cout << "\tveo_get_sym():\tfailed to find symbol." << std::endl;
    std::exit (EXIT_FAILURE);
  }
  return symbol;
}

void wrapper_veo_alloc_mem (veo_proc_handle* h, uint64_t* addr, const size_t size) {
  int status = veo_alloc_mem (h, addr, size);
  switch (status) {
    case  0:
      #ifdef PRINT_ALL_VEO_API
      std::cout << "\tveo_alloc_mem():\tmemory allocation succeeded." << std::endl;
      #endif
      break;
    case -1:
      std::cout << "\tveo_alloc_mem():\tmemory allocation failed: " << xstr(PRINT_FILE_LINE) << std::endl;
      std::exit (EXIT_FAILURE);
      break;
    case -2:
      std::cout << "\tveo_alloc_mem():\tinternal error: " << xstr(PRINT_FILE_LINE) << std::endl;
      std::exit (EXIT_FAILURE);
      break;
  }
}

void wrapper_veo_write_mem (veo_proc_handle* h, uint64_t dst, const void* src, size_t size) {
  int status = veo_write_mem (h, dst, src, size);
  if (status == 0) {
    #ifdef PRINT_ALL_VEO_API
    std::cout << "\tveo_write_mem():\tsuccess." << std::endl;
    #endif
  } else if (status < -1) {
    std::cout << "\tveo_write_mem():\tfailure: " << xstr(PRINT_FILE_LINE) << std::endl;
    std::exit (EXIT_FAILURE);
  } else {
    std::cout << "\tveo_write_mem():\tnot expected!: " << xstr(PRINT_FILE_LINE) << std::endl;
    std::exit (EXIT_FAILURE);
  }
}

void wrapper_veo_read_mem (veo_proc_handle* h, void* dst, uint64_t src, size_t size) {
  int status = veo_read_mem (h, dst, src, size);
  if (status == 0) {
    #ifdef PRINT_ALL_VEO_API
    std::cout << "\tveo_read_mem():\tsuccess." << std::endl;
    #endif
  } else if (status < -1) {
    std::cout << "\tveo_read_mem():\tfailure: " << xstr(PRINT_FILE_LINE) << std::endl;
    std::exit (EXIT_FAILURE);
  } else {
    std::cout << "\tveo_read_mem():\tnot expected!: " << xstr(PRINT_FILE_LINE) << std::endl;
    std::exit (EXIT_FAILURE);
  }
}

void wrapper_veo_free_mem (veo_proc_handle* h, uint64_t addr) {
  int status = veo_free_mem (h, addr);
  switch (status) {
    case  0:
      #ifdef PRINT_ALL_VEO_API
      std::cout << "\tveo_free_mem():\tmemory is successfully freed." << std::endl;
      #endif
      break;
    case -1:
      std::cout << "\tveo_free_mem():\tinternal error: " << xstr(PRINT_FILE_LINE) << std::endl;
      std::exit (EXIT_FAILURE);
      break;
  }
}

veo_args* wrapper_veo_args_alloc (void) {
  veo_args* ptr_args = veo_args_alloc ();
  if (ptr_args == NULL) {
    std::cout << "\tveo_args_alloc():\tthe allocation of veo_args failed: " << xstr(PRINT_FILE_LINE) << std::endl;
    std::exit (EXIT_FAILURE);
  }
  return ptr_args;
}

void wrapper_veo_args_set_i8 (veo_args* ca, int argnum, int8_t val) {
  int status = veo_args_set_i8 (ca, argnum, val);
  if (status == 0) {
    #ifdef PRINT_ALL_VEO_API
    std::cout << "\tveo_args_set_i8():\tsuccess." << std::endl;
    #endif
  }
  else if (status < 0) {
    std::cout << "\tveo_args_set_i8():\tfailure: " << xstr(PRINT_FILE_LINE) << std::endl;
    std::exit (EXIT_FAILURE);
  }
  else {
    std::cout << "\tveo_args_set_i8():\tnot expected!: " << xstr(PRINT_FILE_LINE) << std::endl;
    std::exit (EXIT_FAILURE);
  }
}

void wrapper_veo_args_set_u8 (veo_args* ca, int argnum, uint8_t val) {
  int status = veo_args_set_u8 (ca, argnum, val);
  if (status == 0) {
    #ifdef PRINT_ALL_VEO_API
    std::cout << "\tveo_args_set_u8():\tsuccess." << std::endl;
    #endif
  }
  else if (status < 0) {
    std::cout << "\tveo_args_set_u8():\tfailure: " << xstr(PRINT_FILE_LINE) << std::endl;
    std::exit (EXIT_FAILURE);
  }
  else {
    std::cout << "\tveo_args_set_u8():\tnot expected!: " << xstr(PRINT_FILE_LINE) << std::endl;
    std::exit (EXIT_FAILURE);
  }
}

void wrapper_veo_args_set_i32 (veo_args* ca, int argnum, int32_t val) {
  int status = veo_args_set_i32 (ca, argnum, val);
  if (status == 0) {
    #ifdef PRINT_ALL_VEO_API
    std::cout << "\tveo_args_set_i32():\tsuccess." << std::endl;
    #endif
  }
  else if (status < 0) {
    std::cout << "\tveo_args_set_i32():\tfailure: " << xstr(PRINT_FILE_LINE) << std::endl;
    std::exit (EXIT_FAILURE);
  }
  else {
    std::cout << "\tveo_args_set_i32():\tnot expected!: " << xstr(PRINT_FILE_LINE) << std::endl;
    std::exit (EXIT_FAILURE);
  }
}

void wrapper_veo_args_set_u32 (veo_args* ca, int argnum, uint32_t val) {
  int status = veo_args_set_u32 (ca, argnum, val);
  if (status == 0) {
    #ifdef PRINT_ALL_VEO_API
    std::cout << "\tveo_args_set_u32():\tsuccess." << std::endl;
    #endif
  }
  else if (status < 0) {
    std::cout << "\tveo_args_set_u32():\tfailure: " << xstr(PRINT_FILE_LINE) << std::endl;
    std::exit (EXIT_FAILURE);
  }
  else {
    std::cout << "\tveo_args_set_u32():\tnot expected!: " << xstr(PRINT_FILE_LINE) << std::endl;
    std::exit (EXIT_FAILURE);
  }
}

void wrapper_veo_args_set_u64 (veo_args* ca, int argnum, uint64_t val) {
  int status = veo_args_set_u64 (ca, argnum, val);
  if (status == 0) {
    #ifdef PRINT_ALL_VEO_API
    std::cout << "\tveo_args_set_u64():\tsuccess." << std::endl;
    #endif
  }
  else if (status < 0) {
    std::cout << "\tveo_args_set_u64():\tfailure: " << xstr(PRINT_FILE_LINE) << std::endl;
    std::exit (EXIT_FAILURE);
  }
  else {
    std::cout << "\tveo_args_set_u64():\tnot expected!: " << xstr(PRINT_FILE_LINE) << std::endl;
    std::exit (EXIT_FAILURE);
  }
}

void wrapper_veo_args_set_float (veo_args* ca, int argnum, float val) {
  int status = veo_args_set_float (ca, argnum, val);
  if (status == 0) {
    #ifdef PRINT_ALL_VEO_API
    std::cout << "\tveo_args_set_float():\tsuccess." << std::endl;
    #endif
  }
  else if (status < 0) {
    std::cout << "\tveo_args_set_float():\tfailure: " << xstr(PRINT_FILE_LINE) << std::endl;
    std::exit (EXIT_FAILURE);
  }
  else {
    std::cout << "\tveo_args_set_float():\tnot expected!: " << xstr(PRINT_FILE_LINE) << std::endl;
    std::exit (EXIT_FAILURE);
  }
}

void wrapper_veo_args_set_stack (veo_args* ca, enum veo_args_intent inout, int argnum, char* buff, size_t len) {
  // VEO 2.5.0, only VEO_INTENT_IN is supported
  if (inout != VEO_INTENT_IN) {
    std::cout << "\twrapper_veo_args_set_stack():\tonly intent IN args passing is supported" << std::endl;
    std::exit (EXIT_FAILURE);
  }
  // Size of arguments passed on the stack is limited to 63MB.
  // A way of staying wwll below that value is e.g. to check args sizes are lower 16 MB
  const size_t MB   = 1024 * 1024;
  const size_t __16MB = 16 * MB;
  const size_t __32MB = 32 * MB;
  const size_t __63MB = 63 * MB;

  if (len < __16MB) {
    #ifdef PRINT_ALL_VEO_API
    std::cout << "\twrapper_veo_args_set_stack():\targ size passed to stack is below\t" << sizeMB(__16MB) << "\tMB" << std::endl;
    #endif
  }
  else if (len < __32MB) {
    std::cout << "\twrapper_veo_args_set_stack():\targ size passed to stack is below\t" << sizeMB(__32MB) << "\tMB" << std::endl;
  }
  else if (len < __63MB) {
    std::cout << "\twrapper_veo_args_set_stack():\targ size passed to stack is below\t" << sizeMB(__63MB) << "\tMB" << std::endl;
  }
  else {
    std::cout << "\twrapper_veo_args_set_stack():\targ passed to stack is too large!\t" << std::endl;
    std::exit (EXIT_FAILURE);
  }

  // Actual stack allocation
  int status = veo_args_set_stack (ca, inout, argnum, buff, len);
  if (status == 0) {
    #ifdef PRINT_ALL_VEO_API
    std::cout << "\tveo_args_set_stack():\targument is successfully set." << std::endl;
    #endif
  }
  else if (status == -1) {
    std::cout << "\tveo_args_set_stack():\ten error occurred: " << xstr(PRINT_FILE_LINE) << std::endl;
    std::exit (EXIT_FAILURE);
  }
  else {
    std::cout << "\tveo_args_set_stack():\tnot expected!: " << xstr(PRINT_FILE_LINE) << std::endl;
    std::exit (EXIT_FAILURE);
  }
}

uint64_t wrapper_veo_call_async_by_name (veo_thr_ctxt* ctx, uint64_t libhdl, const char* symname, veo_args* args) {
  uint64_t requested_id =  veo_call_async_by_name (ctx, libhdl, symname, args);
	if (requested_id == VEO_REQUEST_ID_INVALID) {
    std::cout << "\tveo_call_async_by_name():\trequest failed: " << xstr(PRINT_FILE_LINE) << std::endl;
    std::exit (EXIT_FAILURE);
	}
}

void wrapper_veo_call_wait_result (veo_thr_ctxt* ctx, uint64_t reqid, uint64_t* retp) {
  int status = veo_call_wait_result (ctx, reqid, retp);
	switch (status) {
		case VEO_COMMAND_OK:
      #ifdef PRINT_ALL_VEO_API
      std::cout << "\tveo_call_wait_result():\tfunction is successfully returned." << std::endl;
      #endif
      break;
		case VEO_COMMAND_EXCEPTION:
      std::cout << "\tveo_call_wait_result():\tan exception ocurred on execution: " << xstr(PRINT_FILE_LINE) << std::endl;
      std::exit (EXIT_FAILURE);
      break;
		case VEO_COMMAND_ERROR:
      std::cout << "\tveo_call_wait_result():\tan error ocurred on execution: " << xstr(PRINT_FILE_LINE) << std::endl;
      std::exit (EXIT_FAILURE);
      break;
		case VEO_COMMAND_UNFINISHED:
      std::cout << "\tveo_call_wait_result():\tfunction is not finished: " << xstr(PRINT_FILE_LINE) << std::endl;
      std::exit (EXIT_FAILURE);
      break;
		case -1:
      std::cout << "\tveo_call_wait_result():\tinternal error: " << xstr(PRINT_FILE_LINE) << std::endl;
      std::exit (EXIT_FAILURE);
      break;
	}
}
