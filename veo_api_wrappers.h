#ifndef VEO_API_WRAPPERS_H_
#define VEO_API_WRAPPERS_H_

#include <ve_offload.h>
#include <iostream>
#include <cstdlib>

// Function prototypes

// https://veos-sxarr-nec.github.io/veoffload/group__veoapi.html
void wrapper_veo_api_version ();
veo_proc_handle* wrapper_veo_proc_create (int venode);
void wrapper_veo_proc_destroy (veo_proc_handle* proc);
uint64_t wrapper_veo_load_library (veo_proc_handle* proc, const char* libname);

veo_thr_ctxt* wrapper_veo_context_open (veo_proc_handle* proc);
void wrapper_veo_context_close (veo_thr_ctxt* ctx);
uint64_t wrapper_veo_get_sym (veo_proc_handle* proc, uint64_t libhdl, const char* symname);
void wrapper_veo_alloc_mem (veo_proc_handle* h, uint64_t* addr, const size_t size);
void wrapper_veo_write_mem (veo_proc_handle* h, uint64_t dst, const void* src, size_t size);
void wrapper_veo_read_mem (veo_proc_handle* h, void* dst, uint64_t src, size_t size);
void wrapper_veo_free_mem (veo_proc_handle* h, uint64_t addr);

veo_args* wrapper_veo_args_alloc (void);
void wrapper_veo_args_set_i8 (veo_args* ca, int argnum, int8_t val);
void wrapper_veo_args_set_u8 (veo_args* ca, int argnum, uint8_t val);
void wrapper_veo_args_set_i32 (veo_args* ca, int argnum, int32_t val);
void wrapper_veo_args_set_u32 (veo_args* ca, int argnum, uint32_t val);
void wrapper_veo_args_set_u64 (veo_args* ca, int argnum, uint64_t val);
void wrapper_veo_args_set_float (veo_args* ca, int argnum, float val);
void wrapper_veo_args_set_stack (veo_args* ca, enum veo_args_intent inout, int argnum, char* buff, size_t len);

uint64_t wrapper_veo_call_async_by_name (veo_thr_ctxt* ctx, uint64_t libhdl, const char* symname, veo_args* args);
void wrapper_veo_call_wait_result (veo_thr_ctxt* ctx, uint64_t reqid, uint64_t* retp);

#endif /* VEO_API_WRAPPERS_H_ */
